#include <iostream>
#include <vector>
using namespace std;

inline void transpose_scalar_block(float *A, float *B, const int lda, const int ldb, const int block_size)
{
    for(int i=0; i<block_size; i++) {
        for(int j=0; j<block_size; j++) {
            B[j*ldb + i] = A[i*lda +j];
        }
    }
}

inline void transpose_block(float *A, float *B, const int n, const int m, const int lda, const int ldb, const int block_size)
{
    for(int i=0; i<n; i+=block_size) {
        for(int j=0; j<m; j+=block_size) {
            transpose_scalar_block(&A[i*lda +j], &B[j*ldb + i], lda, ldb, block_size);
        }
    }
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

int main()
{
  vector<vector<int32_t>> matrix = {{1,2,3}, {4,5,6}};
  vector<vector<int32_t>> result = MatrixTranspose(matrix);
  for (size_t i = 0; i < result.size(); ++i)
  {
    for (size_t j = 0; j < result[i].size(); ++j)
    {
      cout<<result[i][j]<<"\t";
    }
    cout<<endl;
  }
  return 0;
}
