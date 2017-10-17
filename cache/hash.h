#include <cstring>
#include <cassert>
#include <stdint.h>
#include <iostream>

using namespace std;

inline uint32_t DecodeFixed32(const char* ptr)
{
  uint32_t result;
  memcpy(&result, ptr, sizeof(result));  // gcc optimizes this to a plain load
  return result;
}

void EncodeFixed32(char* buf, uint32_t value) {
  memcpy(buf, &value, sizeof(value));
}

void PutFixed32(std::string* dst, uint32_t value) {
  char buf[sizeof(value)];
  EncodeFixed32(buf, value);
  dst->append(buf, sizeof(buf));
}

static std::string EncodeKey(int k) {
  std::string result;
  PutFixed32(&result, k);
  return result;
}

static int DecodeKey(const string& k) {
  assert(k.size() == 4);
  return DecodeFixed32(k.data());
}

static void* EncodeValue(uintptr_t v) { return reinterpret_cast<void*>(v); }
static int DecodeValue(void* v) { return reinterpret_cast<uintptr_t>(v); }

uint32_t Hash(const char* data, size_t n, uint32_t seed) {
  // Similar to murmur hash
  const uint32_t m = 0xc6a4a793;
  const uint32_t r = 24;
  const char* limit = data + n;
  uint32_t h = seed ^ (n * m);

  while (data + 4 <= limit) {
    uint32_t w = DecodeFixed32(data);
    data += 4;
    h += w;
    h *= m;
    h ^= (h >> 16);
  }

  // Pick up remaining bytes
  switch (limit - data) {
    case 3:
      h += static_cast<unsigned char>(data[2]) << 16;
    case 2:
      h += static_cast<unsigned char>(data[1]) << 8;
    case 1:
      h += static_cast<unsigned char>(data[0]);
      h *= m;
      h ^= (h >> r);
      break;
  }
  return h;
}


