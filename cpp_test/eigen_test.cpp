#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;

  float data[] = {1,2,3,4};
  Map<Vector3f> v1(data);       // uses v1 as a Vector3f object
  Map<ArrayXf>  v2(data,2);     // uses v2 as a ArrayXf object
  Map<Array22f> m1(data);       // uses m1 as a Array22f object
  cout << m1 << endl;
  cout << m1 * v2 << endl;
  Map<MatrixXf> m2(data,2,2);   // uses m2 as a MatrixXf object
  return 0;
}
