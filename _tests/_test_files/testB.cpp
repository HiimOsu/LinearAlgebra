#include "gtest/gtest.h"

#include <iostream>

#include "..\..\includes\VectorCollections\nVector.h"
#include "..\..\includes\VectorCollections\VectorCollections.h"

using namespace std;

float dotArray(const float* arr1, const float* arr2, int count)
{
  float value = 0;
  for(int i = 0; i < count; ++i)
  {
    value += arr1[i] * arr2[i] * arr1[i] * arr2[i];
  }

  return value;
}

TEST(nVectorTest, ModiferTest){
    cout << "Entering VectorModiferTest\n";
    nVector<float,nVecFunc::addArray, nVecFunc::mulArray, nVecFunc::negArray, dotArray> v1(3);

    v1[0] = 3;
    v1[1] = 5;
    v1[2] = 6;

    nVector<float,nVecFunc::addArray, nVecFunc::mulArray, nVecFunc::negArray, dotArray> v2(v1);
    cout << "v1: " << v1.to_string() << endl;
    cout << "v2: " << to_string(v2) << endl;

    cout << "the dot product of v1 and v2 : " << nVector<float,nVecFunc::addArray, nVecFunc::mulArray, nVecFunc::negArray, dotArray>::dotProduct(v1, v2) << endl;
    cout << "the dot product of v1 ^ 2: " << nVector<float,nVecFunc::addArray, nVecFunc::mulArray, nVecFunc::negArray, dotArray>::dotProduct(v1, v1) << endl;

    cout << "v1 + v2 : " << v1 + v2 << endl;
    cout << "v1 - v2: " << v1 - v2 << endl;
    cout << "v1 + 2*v2: " << v1 + 2*v2 << endl;
    
}

TEST(VectorCollections, vector2f)
{
  DAM::Vector2f a({1,2}), b(a);
  cout << a.x() << " " << a.y() << endl;

  a = {3,4};
  cout << a << endl;
  cout << a * 2 << endl;
  cout << 2 * a << endl;
  cout << a / 2 << endl;
  cout << a + a <<endl;
  cout << a - a << endl;
  cout << a * a << endl;

  a = a + a;
  cout << "a+a: " << a << endl;
  cout << "b" << b << endl;
}

TEST(VectorCollections, vector3f)
{
  DAM::Vector3f a({1,2,6}), b(a);
  cout << a.to_string() << endl;
  cout << a * 2 << endl;
  cout << a / 2 << endl;
  cout << a + a <<endl;
  cout << a - a << endl;
  cout << a * a << endl;
  a = a + a;
  cout << "a+a: " << a << endl;
  cout << "b" << b << endl;
  cout << "b.normalize && length : " << b.normalize() << " + " << b.length() << endl; 
  cout << "b.normal length: " << b.normalize().length() << endl;

}

TEST(LinearAlgebra, MatrixTest){
  int col_n = 15;
  int row_m = 15;

  Mat<float> m1(col_n, row_m);
  Mat<float> m2 = Mat<float>(
    {{1,2},
     {1,2}},
    2,2);
  Mat<float> m3 = m2;
  Mat<float> m4 = m3;

  m4 = {{3.5,4}, {3.5,4}};
  
  cout << "m1:\n" << to_string(m1) << endl;
  cout << "m2: \n" << to_string(m2) << endl;
  cout << "m3:\n" << m3 << endl; 
  cout << "m4: \n" << m4 << endl;

  cout << "m3 + m4:\n" << Mat<float>::mat_matAdd(m4,m3) << endl;
  // cout << "m3 X m4:\n" << MatBase<float,int>::mat_matMul(m3,m4) << endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}