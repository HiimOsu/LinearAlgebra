#include "gtest/gtest.h"

#include <iostream>

#include "..\..\includes\VectorCollections\nVector.h"
#include "..\..\includes\VectorCollections\VectorCollections.h"

using namespace std;


TEST(nVectorTest, ModiferTest){
    cout << "Entering VectorModiferTest\n";
    nVector<double> v1(3);

    v1[0] = 3;
    v1[1] = 5;
    v1[2] = 6;

    nVector<double> v2(v1);
    cout << "v1: " << v1.to_string() << endl;
    cout << "v2: " << to_string(v2) << endl;

    cout << "the dot product of v1 and v2 : " << nVector<double>::dot_product(v1, v2) << endl;
    cout << "the dot product of v1 ^ 2: " << nVector<double>::dot_product(v1, v1) << endl;

    cout << "v1 + v2 : " << v1 + v2 << endl;
    cout << "v1 - v2: " << v1 - v2 << endl;
    cout << "v1 + 2*v2: " << v1 + 2*v2 << endl;
    
}

TEST(VectorCollections, vector2f)
{
  DAM::Vector2f a({1,2}), b(a);
  cout << a.x() << " " << a.y() << endl;

  a = {3,4};
  a = a + a;
  cout << a.to_string() << endl;
  cout << a * 2 << endl;
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
  int col_n = 10;
  int row_m = 10;

  Mat<int> m1(col_n, row_m);

  cout << to_string(m1) << endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}