#include <blitz/array.h>
#include <iostream>
#include <random>
#include <sys/time.h>

using namespace std;
using namespace blitz;

template<typename Type>
Type random(Type min, Type max)
{
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<Type> unif(min, max);
   return unif(gen);
}
uint64_t GetCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

template <typename Type>
vector<Type> GenVector(Type min, Type max, int size)
{
  vector<Type> result;
  result.reserve(size);
  for (int i = 0; i < size; ++i)
  {
    result.push_back(random(min, max));
  }
  return result;
}

void Product(Array<double, 2>& matrix1, Array<double, 2>& matrix2, Array<double, 2>& result)
{
  firstIndex i;
  secondIndex j;
  thirdIndex k;
  result = sum(matrix1(i, k) * matrix2(k, j), k);
}

template<class Type>
void Product(Array<Type, 1>& input_array, Array<Type, 2>& input_matrix, Array<Type, 1>& result)
{
  firstIndex i;
  secondIndex j;
  result = sum(input_array(j) * input_matrix(i,j), j);
//    for (int i = 0; i < input_matrix.rows(); ++i)
//    {
//       result(i) = sum(input_array * input_matrix(i, Range::all()));
//    }
}

vector<double> Product(vector<double>& array, vector<vector<double>>& matrix)
{
  vector<double> result;
  result.reserve(matrix.size());
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    double sum = 0;
    for (size_t j = 0; j < matrix[i].size() && j < array.size(); ++j)
    {
       sum += (array[j] * matrix[i][j]);
    }
    result.push_back(sum);
  }
  return result;
}

void TestBlitz()
{
  int times = 10;
  uint64_t total_blitz_time = 0, total_common_time = 0;

  double min = 0, max = 10;
  int cand_size = 30, node_size = 10;
  int rows = 30, cols = 64 * (node_size + (node_size*(node_size-1) >> 1));

  for (int time = 0; time < times; ++time)
  {
    vector<double> seed = GenVector(min, max, cols);
    Array<double, 1> array(seed.data(), seed.size(), neverDeleteData);

    vector<vector<double>> weights;
    Array<double, 2> matrix(rows, cols);
    for (int row = 0; row < rows; ++row)
    {
      vector<double> values = GenVector(min, max, cols);
      Array<double, 1> array(values.data(), values.size(), neverDeleteData);
      matrix(row, Range::all()) = array;
      weights.push_back(values);
    }

    uint64_t common_start = GetCurrentTime();
    vector<double> common_result = Product(seed, weights);
    uint64_t common_exec_time = GetCurrentTime() - common_start;


    uint64_t blitz_start = GetCurrentTime();
    Array<double, 1> blitz_result(rows);
    Product(array, matrix, blitz_result);
    uint64_t blitz_exec_time = GetCurrentTime() - blitz_start;

    total_blitz_time += blitz_exec_time;
    total_common_time += common_exec_time;
  }
  cout <<"total blitz time : "<< total_blitz_time <<"ms"<<endl;
  cout <<"total common time : "<< total_common_time <<"ms"<<endl;
//  cout << "result " << result << endl;
//  for (size_t i = 0; i < weights.size(); ++i)
//  {
//    for (auto it = weights[i].begin(); it != weights[i].end(); ++it)
//    {
//       cout <<*it << "\t";
//    }
//    cout << endl;
//  }
}


void Test()
{
  Array<float,1> x(4), y(4), result(4);
  x = 1, 2, 3, 4;
  y = 1, 0, 0, 1;
  Array<float,2> A(4,4), B(4, 4), C(4, 4);
  firstIndex i;
  secondIndex j;

  A = x(i) * y(j);
  cout << A << endl;
//  B = A.transpose(secondDim, firstDim);
  Array<float,1> sub_array(A(0, Range::all()));
  cout << sub_array << endl;
//  B = A.transpose(secondDim, firstDim);
//  C = x(j) * B(i,j);
//  result = sum(C, j);
//  cout << C << endl;
//  cout << C.rows() << C.cols() << endl;
//  cout << result << endl;
}

int main()
{
//  Test();
  TestBlitz();
//  MatrixProduct(x, B, result);
  return 0;
}
