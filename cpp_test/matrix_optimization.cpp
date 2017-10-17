#include <iostream>
#include <vector>
#include <iostream>
#include <random>
#include <sys/time.h>
using namespace std;

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

template<class T>
vector<vector<T>> MatrixTranspose(vector<vector<T>>& matrix)
{
  vector<vector<T>> result;
  if (matrix.size() == 0 || matrix[0].size() == 0)
  {
    return result;
  }
  result.resize(matrix[0].size());
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    it->resize(matrix.size());
  }
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[i].size(); ++j)
    {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

void Brck(vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C, const size_t bsize = 4)
{
  if (A.empty() || B.empty())
  {
    return;
  }
  if (A.size() != B.size())
  {
    return;
  }
  size_t M = A.size(), N = B.size(), K = A[0].size();
  size_t r, c, k, kk, cc;
  double sum;
  int en = bsize * (K / bsize);

  C.resize(M);
  for (r = 0; r < M; r++)
  {
    C[r].resize(N, 0);
  }

  for (kk = 0; kk < en; kk += bsize)
  {
    for (cc = 0; cc < en; cc += bsize)
    {
      for (r = 0; r < M; r++)
      {
        for (c = cc; c < cc + bsize && c < N; c++)
        {
          sum = C[r][c];
          for (k = kk; k < kk + bsize; k++)
          {
             sum += A[r][k]*B[c][k];
          }
          C[r][c] = sum;
        }
      }
    }

    for (r = 0; r < M; r++)
    {
      for (c = en; c < N; c++)
      {
        sum = C[r][c];
        for (k = kk; k < kk + bsize; k++)
        {
           sum += A[r][k] *B[c][k];
        }
        C[r][c] = sum;
      }
    }
  }

  for (cc = 0; cc < en; cc += bsize)
  {
    for (r = 0; r < M; r++)
    {
      for (c = cc; c < cc + bsize && c < N; c++)
      {
        sum = C[r][c];
        for (kk = en; kk < K; kk++)
        {
          sum += A[r][kk]*B[c][kk];
        }
        C[r][c] = sum;
      }
    }
  }
}
void TransProduct(vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C)
{
  if (A.empty() || B.empty())
  {
    return;
  }
  if (A.size() != B.size())
  {
    return;
  }
  size_t M = A.size(), N = B.size(), KK = B[0].size();

  C.resize(M);
  for (size_t r = 0; r < M; r++)
  {
    C[r].resize(N, 0);
  }

  for (size_t i = 0; i < M; ++i)
  {
    for (size_t j = 0; j < N; ++j)
    {
      double sum = 0;
      for (size_t k = 0; k < KK; ++k)
      {
        sum = sum + (A[i][k] * B[j][k]);
      }
      C[i][j] = sum;
    }
  }
}

void General(vector<vector<double>>& A, vector<vector<double>>& B, vector<vector<double>>& C)
{
  if (A.empty() || B.empty())
  {
    return;
  }
  if (A[0].size() != B.size())
  {
    return;
  }
  size_t M = A.size(), K = B.size(), N = B[0].size();

  C.resize(M);
  for (size_t r = 0; r < M; r++)
  {
    C[r].resize(N, 0);
  }

  for (size_t i = 0; i < M; ++i)
  {
    for (size_t j = 0; j < N; ++j)
    {
      for (size_t kk = 0; kk < K; ++kk)
      {
        C[i][j] = C[i][j] + (A[i][kk] * B[kk][j]);
      }
    }
  }
}

void Compare()
{
  int times = 50;
  uint64_t total_brck_time = 0, total_trans_time = 0, total_common_time = 0;

  double min = 0, max = 10;
  int rows = 32, cols = 1024;
  for (int time = 0; time < times; ++time)
  {
    vector<vector<double>> A, B, C, D, E;
    for (size_t i = 0; i < rows; ++i)
    {
      A.push_back(GenVector(min, max, cols));
    }
    for (size_t i = 0; i < cols; ++i)
    {
      B.push_back(GenVector(min, max, rows));
    }

    uint64_t common_start = GetCurrentTime();
    General(A, B, D);
    uint64_t common_exec_time = GetCurrentTime() - common_start;

    vector<vector<double>> trans_B = MatrixTranspose(B);
    uint64_t brck_start = GetCurrentTime();
    Brck(A, trans_B, C, 8);
    uint64_t brck_exec_time = GetCurrentTime() - brck_start;

    uint64_t trans_start = GetCurrentTime();
    TransProduct(A, trans_B, E);
    uint64_t trans_exec_time = GetCurrentTime() - trans_start;

    total_brck_time += brck_exec_time;
    total_trans_time += trans_exec_time;
    total_common_time += common_exec_time;
  }
  cout <<"total brck time : "<< total_brck_time <<"ms"<<endl;
  cout <<"total trans time : "<< total_trans_time <<"ms"<<endl;
  cout <<"total common time : "<< total_common_time <<"ms"<<endl;

}
int main()
{
    Compare();
//  vector<vector<double>> A =
//  {
//   {1, 2, 3, 4, 5, 6},
//   {2, 3, 4, 5, 6, 7},
//   {2, 3, 4, 5, 6, 7},
//  };
//
//  vector<vector<double>> B =
//  {
//   {1, 1, 2},
//   {1, 2, 3},
//   {1, 3, 4},
//   {1, 4, 5},
//   {1, 5, 6},
//   {1, 6, 7},
//  };
//
//  vector<vector<double>> C;
//  General(A, B, C);
//  for (size_t i = 0; i < C.size(); ++i)
//  {
//    for (size_t j = 0; j < C[i].size(); ++j)
//    {
//      cout << C[i][j] << "\t";
//    }
//    cout << endl;
//  }
//  cout << endl;
//
//  vector<vector<double>> trans_B = MatrixTranspose(B);
//  vector<vector<double>> D;
//  Brck(A, trans_B, D, 4);
//  for (size_t i = 0; i < D.size(); ++i)
//  {
//    for (size_t j = 0; j < D[i].size(); ++j)
//    {
//      cout << D[i][j] << "\t";
//    }
//    cout << endl;
//  }
  return 0;
}


