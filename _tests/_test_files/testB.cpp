#include "gtest/gtest.h"

#include <iostream>

#include "..\..\includes\nVector.h"

using namespace std;


TEST(nVectorTest, DISABLED_ModiferTest){
    cout << "Entering VectorModiferTest\n";
    nVector<double> v1(3);

    v1[0] = 3;
    v1[1] = 5;
    v1[2] = 6;

    nVector<double> v2(v1);
    cout << "v1: " << v1.to_string() << endl;
    cout << "v2: " << v2.to_string() << endl;

    cout << "the dot product of v1 and v2 : " << dot_product(v1, v2) << endl;
    cout << "the dot product of v1 ^ 2: " << dot_product(v1, v1) << endl;

    cout << "v1 + v2 : " << v1 + v2 << endl;
    cout << "v1 - v2: " << v1 - v2 << endl;
    cout << "v1 + 2*v2: " << v1 + 2*v2 << endl;

}

TEST(LinearAlgebra, Chapter3_5_Q7){
  nVector<int> v1 = {2, -3, 4, -1, 7},
  v2 = {-3, 2, -1, 4, 2}, 
  v3 = {5, -6, 7 , -4, 10};

  cout << "v1: " << v1 << "\nv2: " << v2 << "\nv3: " << v3 << endl;

  cout << "\n\n\n";

  nVector<int> u1 = v1 + 8*v2 - 5 * v3,
  u2 = 5*v2 - 3*v3,
  u3 = 2*v2 - v3;

  cout << "u1: " << u1 << endl;
  cout << "u2: " << u2 << endl;
  cout << "u3: " << u3 << endl;


  cout << "T(<1,-2,1>)L: " << u1 - 2*u2 + u3 << endl;
  cout << "T(<0,-1,3>)L: " << -u2 + 3*u3 << endl;
  cout << "T(<0,-2,5>)L: " << - 2*u2 + 5*u3 << endl;

  nVector<int> r1 = {-4, -2, -1},
  r2 = {-1, 6, -1},
  r3 = {-39, -26, -9},
  r4 = {51, 32, 12},
  r5 = {-27, -20, -6};

  cout << "\n\n1st:\n"
  << "r1: " << (r1 = r1 - 4*r2) << endl
  << "r3: " << (r3 = r3 - 39 * r2) << endl
  << "r4: " << (r4 = r4 + 51 * r2) << endl
  << "r5: " << (r5 = r5 - 27*r2) << endl;
  
  cout<< "r2: " << (r2 = -r2) << endl;

}

TEST(LinearAlgebra, MatrixTest){
  typedef nVector<float> col_t;
  // col_t* vectorArrayPointer = new col_t[10];

  // cout << *vectorArrayPointer << endl;

}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}