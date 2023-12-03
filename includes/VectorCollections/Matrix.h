#include <iostream>
#include <iomanip>

#include "nVector.h"
#include "VectorCollections.h"

template<class value_t>
class Mat
{
private:
    typedef int size_t;
    nVector<value_t>* mat;
    size_t row_n, col_n;
public:
//Constructor
    Mat(const std::initializer_list<std::initializer_list<float>>& c, int row_n, int col_n)
    {
        if(col_n < 1 || row_n < 1) assert(false && "Mat<value_t>(std::initializer_list)");

        this->row_n = row_n;
        this->col_n = col_n;

        mat = new nVector<value_t>[row_n];
        if(c.size() != row_n) assert(false && "Mat<value_t>(std::initializer_list)");

        int i = 0;
        for(auto coli : c){
            if(coli.size() != col_n) assert(false && "Mat<value_t>(std::initializer_list)");
        //because arr[] initializer uses default constructor from nVector
        //and we need to allocate each vector in the array of vect
            mat[i].change_order(col_n);
            mat[i++] = coli;
        }
    }

    Mat(int row_n, int col_n)
    {
        if(col_n < 1 || row_n < 1) assert(false && "Mat<value_t>(std::initializer_list)");

        this->row_n = row_n;
        this->col_n = col_n;

        mat = new nVector<value_t>[row_n];
        for(int i = 0; i < row_n; ++i){
            mat[i].changeOrder(col_n);
        }
    }

//Big3
    Mat(const Mat& copy_me)
    {
        this->col_n = copy_me.col_n;
        this->row_n = copy_me.row_n;
        mat = new nVector<value_t>[row_n];
        for(int i = 0; i < row_n; ++i){
        //because arr[] initializer uses default constructor from nVector
        //and we need to allocate each vector in the array of vect
            mat[i].changeOrder(col_n);
            mat[i] = copy_me.mat[i];
        }

    }
    Mat& operator=(const Mat& assign_me)
    {
        if(col_n != assign_me.col_n || row_n != col_n) assert(false && "Mat<value_t> operator=(const Mat& assign_me)");
        for(int i = 0; i < row_n; ++i){
            mat[i] = assign_me.mat[i];
        }
    }
    ~Mat()
    {
        if(mat) delete mat;
    }

//CopyConstructor:
//Assignment operator:

    nVector<value_t>& operator[] (size_t i)
    {
        if(i >= row_n || i < 0) assert(false);
        return mat[i];
    }
//String:
    friend std::string to_string(const Mat& m)
    {
        std::stringstream ss;
        for(int i =0 ;i < m.row_n; ++i)
            ss << m.mat[i] << std::endl;
        return ss.str();
    }
};