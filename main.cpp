#include <iostream>

#include "includes\nVector.h"
using namespace std;

int main(){
    cout << "Entering Main\n";
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