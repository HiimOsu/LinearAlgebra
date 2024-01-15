#ifndef MATRIX_CPP
#define MATRIX_CPP 
#include "Matrix.hpp"



//Standard Operator
template <class value_t>
Mat<value_t>  Mat<value_t>::mat_matAdd(const Mat& m1, const Mat& m2)
{
    if(m1.col_n != m2.col_n) assert(false&& "mat_matAdd_____Dimension misMatch M1 + M2");
    if(m1.row_n != m2.row_n) assert(false&& "mat_matAdd_____Dimension misMatch M1 + M2");

    Mat<value_t> m3(m1);
    size_t row_size = m1.getSize_Row();
    nVecFunc::addArray(m3.begin(), m2.begin(), row_size);
    return m3;
}

template <class value_t>
Mat<value_t>  Mat<value_t>::mat_scalMul(const Mat& m1, value_t scal)
{
    Mat<value_t> m3(m1);
    size_t row_size = m1.getSize_Row();
    nVecFunc::mulArray(m3.begin(), scal, row_size);
    return m3;
}

template <class value_t>
Mat<value_t> Mat<value_t>::mat_matMul(const Mat<value_t>& m1, const Mat<value_t>& m2)
{
    if(m1.col_n != m2.row_n) assert(false&& "mat_matMul_____Dimension misMatch M1 X M2");
    size_t row_n = m1.getSize_Row();
    size_t col_n = m2.getSize_Col();
    Mat<value_t> m3(row_n, col_n);

    nVector<value_t> vec2(col_n);
    // value_t* vec2_arrptr = vec2.begin();
    for(size_t col_j = 0; col_j < col_n; ++col_j)
    {
        m2.get_col(col_j, vec2.begin());
        m3.set_col(col_j, Mat<value_t>::mat_vecMul(m1, vec2).begin());
    }
    return m3;
}

template <class value_t>
Mat<value_t>  Mat<value_t>::mat_neg(const Mat& m1)
{
    Mat<value_t> m3(m1);
    size_t row_size = m1.getSize_Row();

    for(int i = 0; i < row_size; ++i)
        m3.mat[i] = -m3.mat[i];
    return m3;
}

template <class value_t>
nVector<value_t>  Mat<value_t>::mat_vecMul(const Mat<value_t>& m1, const nVector<value_t>& v1)
{
    int mat_row = m1.getSize_Row();
    int mat_col = m1.getSize_Col();
    nVector<value_t> ret(mat_row);
    value_t entry_i;

    if(mat_col != v1.size())assert(false&& "mat_vecMul_____Dimension misMatch M1 X V1");


    for(int row_i = 0; row_i < mat_row; ++row_i)
    {   
        entry_i = m1[row_i][0] * v1[0];

        for(int col_j = 1; col_j < mat_col; ++col_j){
            entry_i += m1[row_i][col_j] * v1[col_j];
        }

        ret[row_i] = entry_i;
    }

    return ret;
}

//Functional
template <class value_t>
Mat<value_t>  Mat<value_t>::Ref()
{
    Mat m2(*this);

    for(int i = 0; i < row_n && i < col_n-1; ++i)
        m2.reduce_EntryBelowZero(i,i);
    
    return m2;
}

template <class value_t>
Mat<value_t>  Mat<value_t>::Rref()
{
    return *this;
}

//Constructor
template <class value_t>
Mat<value_t>::Mat(const std::initializer_list<std::initializer_list<value_t>>& c, int row_n, int col_n)
{
    if(col_n < 1 || row_n < 1) assert(false && "MatBase<value_t>(std::initializer_list)");

    this->row_n = row_n;
    this->col_n = col_n;

    mat = new nVector<value_t>[row_n];
    if(c.size() != row_n) assert(false && "MatBase<value_t>(std::initializer_list)");

    int i = 0;
    for(auto coli : c){
        if(coli.size() != col_n) assert(false && "MatBase<value_t>(std::initializer_list)");
    //because arr[] initializer uses default constructor from nVector
    //and we need to allocate each vector in the array of vect
        mat[i].changeOrder(col_n);
        mat[i++] = coli;
    }
}

template <class value_t>
Mat<value_t>::Mat(int row_n, int col_n)
{
    if(col_n < 1 || row_n < 1) assert(false && "MatBase<value_t>(std::initializer_list)");

    this->row_n = row_n;
    this->col_n = col_n;

    mat = new nVector<value_t>[row_n];
    for(int i = 0; i < row_n; ++i){
        mat[i].changeOrder(col_n);
        nVecFunc::InitializeArray(mat[i].begin(), value_t(), col_n);
    }
}

//Big3
template <class value_t>
Mat<value_t>::Mat(const Mat& copy_me)
{
    this->col_n = copy_me.col_n;
    this->row_n = copy_me.row_n;
    this->mat = new nVector<value_t>[row_n];
    for(int i = 0; i < row_n; ++i){
    //because arr[] initializer uses default constructor from nVector
    //and we need to allocate each vector in the array of vect
        this->mat[i].changeOrder(col_n);
        this->mat[i] = copy_me.mat[i];
    }

}

template <class value_t>
Mat<value_t>& Mat<value_t>::operator=(const Mat<value_t>& assign_me)
{
    if(col_n != assign_me.col_n || row_n != col_n) assert(false && "MatBase<value_t> operator=(const MatBase& assign_me)");
    for(int i = 0; i < row_n; ++i){
        mat[i] = assign_me.mat[i];
    }
    return *this;
}

template <class value_t>
Mat<value_t>::~Mat()
{
    if(mat) delete mat;
}


//Assignment operator:
template <class value_t>
Mat<value_t>& Mat<value_t>::operator= (const std::initializer_list<std::initializer_list<value_t>>& c)
{
    if(c.size() != row_n) assert(false && "MatBase<value_t>::operator=(std::initializer_list)");
    int i = 0;
    for(auto coli : c){
        if(coli.size() != col_n) assert(false && "MatBase<value_t>::operator=(std::initializer_list)");
        mat[i++] = coli;
    }
    return *this;
}

//Operator
template <class value_t>
Mat<value_t>& Mat<value_t>::operator+ () const
{
    return *this;
}
template <class value_t>
Mat<value_t> Mat<value_t>::operator+ (const Mat& m2) const
{
    return mat_matAdd(*this, m2);
}

template <class value_t>
Mat<value_t>& Mat<value_t>::operator-() const
{
    return mat_neg(*this);
}
template <class value_t>
Mat<value_t> Mat<value_t>::operator-(const Mat& m2) const
{
    return mat_matAdd(*this, -m2);
}

template <class value_t>
Mat<value_t> Mat<value_t>::operator* (value_t scalar) const
{
    return mat_scalMul(*this, scalar);
}
template <class value_t>
Mat<value_t> operator*(value_t scalar, const Mat<value_t>& m1)
{
    return m1.mat_scalMul(m1, scalar);
}
template <class value_t>
Mat<value_t> Mat<value_t>::operator* (const Mat m2)
{
    return mat_matMul(*this, m2);
}


//Getter

template <class value_t>
nVector<value_t> Mat<value_t>::getCol(size_t j) const
{
    nVector<value_t> col(row_n);
    for(int i = 0; i < row_n; ++i)
        col[i] = mat[i][j];
    return col;
}

template <class value_t>
void Mat<value_t>::get_col(size_t col_j, value_t* dest) const
{
    for(int row_i = 0; row_i < this->getSize_Row(); ++row_i)
        dest[row_i] = this->mat[row_i][col_j];
}
//Setter
template <class value_t>
nVector<value_t>& Mat<value_t>::operator[] (size_t i)
{
    if(i >= row_n || i < 0) assert(false);
    return mat[i];
}    
template <class value_t>
const nVector<value_t>& Mat<value_t>::operator[] (size_t i) const
{
    if(i >= row_n || i < 0) assert(false);
    return mat[i];
}


template <class value_t>
void Mat<value_t>::set_col(size_t row_j, value_t* target)
{
    for(int col_i = 0; col_i < this->getSize_Row(); ++col_i)
        this->mat[col_i][row_j] = target[col_i];

}
template <class value_t>
void Mat<value_t>::set_row(size_t row_i, value_t* target)
{
    std::copy(target, target + getSize_Col(), this->mat[row_i].begin());
}


//String:
template <class value_t>
std::string to_string(const Mat<value_t>& m)
{
    std::stringstream ss;
    for(int i =0 ;i < m.row_n; ++i)
        ss << i << "\t:\t" << m.mat[i] << std::endl;
    return ss.str();
}
template <class value_t>
std::ostream& operator<<(std::ostream& outs, const Mat<value_t>& m)
{
    outs << to_string(m);
    return outs;
}

//Helper
template <class value_t>
void Mat<value_t>::reduce_EntryBelowZero(const int& row, const int& col)
{
    if(row < 0 || col < 0 || row>= row_n || col >= col_n) 
        assert(false && "Dev Error::Mat________reduce_EntryBelowZero: Wrong Dim for i and j");
    
    // std::cout << "Reducing  row, col; " << row  << " : " << col  << std::endl;
    // std::cout << "mat[row]: " << mat[row]  << " : " << mat[row].size()<< "\n\n"; 
    // std::cout << *this << "\n\n";

    int i = row;
    if(mat[row][col] != 0)
    {
        // mat[row] /= mat[row][col];
        while (++i < row_n)
        {
            if(mat[i][col] != 0)
                Ero4_SubRow(i, row,(mat[i][col]) / mat[row][col]);
                // mat[i] -= (mat[i][col]) * (mat[row]);
        }
    }
    else
    {
        
        while (mat[++i][col] == 0)
        {
            if(i == row_n - 1) return;
        }
        if(mat[i][col] != 0) Ero2_swapRow(i, row);
    }
}

template <class value_t>

void Mat<value_t>::Ero1_multiplyRow(size_t row, value_t scalar)
{
    mat[row] *= scalar;
}
template <class value_t>

void Mat<value_t>::Ero2_swapRow(size_t row1, size_t row2)
{
    mat[row1].swap(mat[row2]);
}
template <class value_t>

void Mat<value_t>::Ero3_AddRow(size_t dest, size_t target, value_t scalar)
{
    mat[dest] += mat[target] * scalar;
}
template <class value_t>

void Mat<value_t>::Ero4_SubRow(size_t dest, size_t target, value_t scalar)
{
    mat[dest] -= mat[target] * scalar;
}
#endif