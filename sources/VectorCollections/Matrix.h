#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <iomanip>

#include "nVector.h"
#include "VectorCollections.h"

template<class value_t>
class Mat
{
protected:
    typedef int size_t;
    nVector<value_t>* mat;
    size_t row_n, col_n;
public:
//Function
    static Mat mat_matAdd(const Mat& m1, const Mat& m2);
    static Mat mat_scalMul(const Mat& m1, value_t scal);
    static Mat mat_neg(const Mat& m1);
    static Mat mat_matMul(const Mat& m1, const Mat& m2);
    static nVector<value_t> mat_vecMul(const Mat& m, const nVector<value_t>& v);
    
    Mat Ref();
    Mat Rref();
//Constructor
    Mat(const std::initializer_list<std::initializer_list<value_t>>& c, int row_n, int col_n);
    Mat(int row_n, int col_n);
//Big3
    Mat(const Mat& copy_me);
    Mat& operator=(const Mat& assign_me);
    ~Mat();
//Assignment operator:
    Mat& operator= (const std::initializer_list<std::initializer_list<value_t>>& c);
//Operator
    Mat& operator+ () const;
    Mat operator+ (const Mat& m2) const;
    
    Mat& operator-() const;
    Mat operator-(const Mat& m2) const;
   
    Mat operator* (value_t scalar) const;
    
    template<typename value_t2>
    friend operator*(value_t2 scalar, const Mat<value_t2>& m1);
    Mat operator* (const Mat m2);


//Getter

    inline nVector<value_t>* begin()    {return mat;}
    inline nVector<value_t>* begin() const  {return mat;}
    inline nVector<value_t>* end()  {return mat + row_n;}
    inline nVector<value_t>* end() const    {return mat + row_n;}

    nVector<value_t> getCol(size_t j) const;
    inline nVector<value_t> getRow(size_t i) const  {return mat[i];}

    void get_col(size_t col_j, value_t* dest) const;
    inline void get_row(size_t row_i, value_t* dest) const 
    {
        std::copy(this->mat[row_i].begin(), this->mat[row_i].end(), dest);
    }

    inline size_t getSize_Col() const
    {
        return col_n;
    }
    inline size_t getSize_Row() const
    {
        return row_n;
    }
//Setter
    nVector<value_t>& operator[] (size_t i);
    const nVector<value_t>& operator[] (size_t i) const;
    
    value_t& getEntry(size_t row, size_t col){return mat[row][col];}
    const value_t& getEntry(size_t row, size_t col) const{return mat[row][col];}
    
    
    void set_col(size_t row_j, value_t* target);
    void set_row(size_t col_i, value_t* target);
//String:
    template<typename value_t2>
    friend std::string to_string(const Mat<value_t2>& m);
    template<typename value_t2>
    friend std::ostream& operator<<(std::ostream& outs, const Mat<value_t2>& m);
//Helper
private:
    void reduce_EntryBelowZero(const int& row, const int& col);

    void Ero1_multiplyRow(size_t row, value_t scalar);
    void Ero2_swapRow(size_t row1, size_t row2);
    void Ero3_AddRow(size_t dest, size_t target, value_t scalar);
    void Ero4_SubRow(size_t dest, size_t target, value_t scalar);
};

#include "Matrix.cpp"
#endif

