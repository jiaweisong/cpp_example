#include <iostream>
//以下是第二级配置器
class memory_pool
{
public:
  //小块区域的上界
  static const int ALIGN = 8;
  //小块区域的下降
  static const int MAX_BYTES = 128;
  // MAX_BYTES/_ALIGN，有多少个区域
  static const int NFREELISTS = 16;

private:
  //ROUND_UP()将bytes提升至8的倍数
  static size_t ROUND_UP(size_t bytes)
  {
    return ((bytes + ALIGN - 1) & ~(ALIGN - 1));
  }

private:
  //free_lists节点构造
  union obj
  {
    union obj * free_list_link;
    char client_data[1];
  };

private:
  //16个free_lists
  static obj * volatile free_list[NFREELISTS];

  //根据区块大小，决定使用第n号free-list, n从1算
  static size_t FREELIST_INDEX(size_t bytes)
  {
      return (((bytes) + ALIGN - 1) / ALIGN - 1);
  }

  //返回一个大小为n的对象，并可能加入大小为n的其他区块到free list
  static void *refill(size_t n);

  //配置一大块空间，可容纳nobjs个大小为"size"的区块
  //如果配置nobjs个区块有所不便，nobjs可能会降低
  static char* chunk_alloc(size_t size, int& nobjs);

  // chunk allocation state
  static char *start_free;    //内存池起始位置
  static char *end_free;      //内存池结束位置
  static size_t heap_size;

public:
  static void * allocate(size_t n);
  static void deallocate(void *p, size_t n);
  static void * reallocate(void *p, size_t old_sz, size_t new_sz);
};

char *memory_pool::start_free = 0;

char *memory_pool::end_free = 0;

size_t memory_pool::heap_size = 0;

typename memory_pool::obj * volatile memory_pool::free_list[NFREELISTS] =
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void * memory_pool::allocate(size_t n)
{
  obj * volatile *my_free_list;
  obj * result;
  //大于128字节就调用第一级配置器
  if(n > (size_t)MAX_BYTES)
  {
    return malloc(n);
  }
  //寻找16个free lists中适当的一个
  my_free_list = free_list + FREELIST_INDEX(n);
  result = *my_free_list;
  if(result == 0)
  {
    //没找到free_list,准备重新填充free list
    void *r = refill(ROUND_UP(n));
    return r;
  }
  //调整free list
  *my_free_list = result->free_list_link;
  return (result);
}

void memory_pool::deallocate(void *p, size_t n)
{
  obj * volatile *my_free_list = free_list + FREELIST_INDEX(n);
  obj* curr_obj = (obj *)p;
  curr_obj->free_list_link = *my_free_list;
  *my_free_list = curr_obj;
}

void *memory_pool::refill(size_t n)
{
  int nobjs = 20;
  //调用chunk_alloc(),尝试取得nobjs个区块作为free_list的新节点
  //注意参数nobjs是pass by reference
  char * chunk = chunk_alloc(n, nobjs);
  obj * volatile * my_free_list;
  obj * result;
  obj * current_obj, * next_obj;
  int i;

  //如果只获得一个区块，这个区块就分配给调用者，free_list无新节点
  if(1 == nobjs)
      return (chunk);
  //my_free_list指向自己在free_lists中的位置
  my_free_list = free_list + FREELIST_INDEX(n);

  //以下在chunk空间内建立free list
  result = (obj *)chunk;      //这一块准备返回给客端
  //以下导引free_list指向新配置的空间(取自内存池)
  *my_free_list = next_obj = (obj *)(chunk + n);
  //以下将free_list的各节点串接起来
  for(i = 1; ; i++)
  {
    //从1开始，因为第0个将返回给客端
    current_obj = next_obj;
    next_obj = (obj*)((char *)next_obj + n);
    if(nobjs - 1 == i)
    {
      current_obj->free_list_link = 0;
      break;
    }
    else
    {
      current_obj->free_list_link = next_obj;
    }
  }
  return (result);
}

//假设size已经适当上调至8的倍数
//注意参数nobjs是pass bu reference
char* memory_pool::chunk_alloc(size_t size, int& nobjs)
{
  char * result;
  size_t total_bytes = size * nobjs;
  size_t bytes_left = end_free - start_free;  //内存池剩余空间

  if(bytes_left >= total_bytes)
  {
    //内存池剩余空间完全满足需求量
    result = start_free;
    start_free += total_bytes;
    return (result);
  }
  else if(bytes_left >= size)
  {
    //内存池剩余空间不能完全满足需求量，但足够供应一个含以上区块
    nobjs = bytes_left / size;
    total_bytes = size * nobjs;
    result = start_free;
    start_free += total_bytes;
    return (result);
  }
  else
  {
    //内存池剩余空间连一个区块额大小都无法提供
    size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
    //以下试着让内存池的残馀零头还有利用价值
    if(bytes_left > 0)
    {
      //内存池还有一些零头，先配置给适当的free_list
      //首先寻找适当的free_list
      obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
      //调整free_list,将内存池中的残馀空间编入
      ((obj*)start_free)->free_list_link = *my_free_list;
      *my_free_list = (obj*)start_free;
    }

    //配置heap空间，用来补充内存池
    start_free = (char*)malloc(bytes_to_get);
    if(0 == start_free)
    {
      //heap空间不足，malloc()失败
      int i;
      obj *volatile * my_free_list, *p;
      //搜索适当的fee_list
      //适当即"尚有未用区块。且区块足够大"
      for(i = size; i <= MAX_BYTES; i += ALIGN)
      {
        my_free_list = free_list + FREELIST_INDEX(i);
        p = *my_free_list;
        if(0 != p)
        {
          //free_list 内尚有未用区块
          //调整free_list以释放未用区块
          *my_free_list = p->free_list_link;
          start_free = (char*)p;
          end_free = start_free + i;

          return (chunk_alloc(size, nobjs));
        }
      }
      end_free = 0;
      start_free = (char*)malloc(bytes_to_get);
    }
    heap_size += bytes_to_get;
    end_free = start_free + bytes_to_get;

    return (chunk_alloc(size, nobjs));
  }
}

