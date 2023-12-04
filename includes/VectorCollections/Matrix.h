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
//Constructor
    Mat(const std::initializer_list<std::initializer_list<value_t>>& c, int row_n, int col_n)
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

    Mat(int row_n, int col_n)
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
        if(col_n != assign_me.col_n || row_n != col_n) assert(false && "MatBase<value_t> operator=(const MatBase& assign_me)");
        for(int i = 0; i < row_n; ++i){
            mat[i] = assign_me.mat[i];
        }
        return *this;
    }
    ~Mat()
    {
        if(mat) delete mat;
    }

//CopyConstructor:
//Assignment operator:
    Mat& operator= (const std::initializer_list<std::initializer_list<value_t>>& c)
    {
        if(c.size() != row_n) assert(false && "MatBase<value_t>::operator=(std::initializer_list)");
        int i = 0;
        for(auto coli : c){
            if(coli.size() != col_n) assert(false && "MatBase<value_t>::operator=(std::initializer_list)");
            mat[i++] = coli;
        }
        return *this;
    }
//Modifier
    static Mat<value_t> mat_matAdd(const Mat<value_t>& m1, const Mat<value_t>& m2);
    static Mat<value_t> mat_scalMul(const Mat<value_t>& m1, value_t scal);
    static Mat<value_t> mat_matMul(const Mat<value_t>& m1, const Mat<value_t>& m2);

    nVector<value_t>* begin(){return mat;}
    nVector<value_t>* begin() const{return mat;}
    
    nVector<value_t>* end() {return mat+row_n;}
    nVector<value_t>* end() const {return mat+row_n;}

//Getter
    nVector<value_t>& operator[] (size_t i)
    {
        if(i >= row_n || i < 0) assert(false);
        return mat[i];
    }    
    const nVector<value_t>& operator[] (size_t i) const
    {
        if(i >= row_n || i < 0) assert(false);
        return mat[i];
    }
    
    value_t& getEntry(size_t row, size_t col)
    {
        return mat[row][col];
    }
    const value_t& getEntry(size_t row, size_t col) const
    {
        return mat[row][col];
    }
    
    nVector<value_t> getCol(size_t j) const
    {
        nVector<value_t> col(row_n);
        for(int i = 0; i < row_n; ++i)
            col[i] = mat[i][j];
        return col;
    }
    nVector<value_t> getRow(size_t i) const
    {
        return mat[i];
    }
    
    size_t getSize_Col() const{
        return col_n;
    }
    size_t getSize_Row() const{
        return row_n;
    }
//String:
    friend std::string to_string(const Mat& m)
    {
        std::stringstream ss;
        for(int i =0 ;i < m.row_n; ++i)
            ss << i << "\t:\t" << m.mat[i] << std::endl;
        return ss.str();
    }
    friend std::ostream& operator<<(std::ostream& outs, const Mat<value_t>& m)
    {
        outs << to_string(m);
        return outs;
    }
    
};

template <class value_t>
Mat<value_t>  Mat<value_t>::mat_matAdd(const Mat<value_t>& m1, const Mat<value_t>& m2)
{
    if(m1.col_n != m2.col_n) assert(false&& "mat_matAdd_____Dimension misMatch M1 + M2");
    if(m1.row_n != m2.row_n) assert(false&& "mat_matAdd_____Dimension misMatch M1 + M2");

    Mat<value_t> m3(m1);
    size_t row_size = m1.getSize_Row();
    nVecFunc::addArray(m3.begin(), m2.begin(), row_size);
    return m3;
}

template <class value_t>
Mat<value_t>  Mat<value_t>::mat_scalMul(const Mat<value_t>& m1, value_t scal)
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

    size_t row_n = m1.getSize_Col(),
    col_n = m2.getSize_Row();
    Mat<value_t> m3(row_n, col_n);

    for(size_t i = 0; i < row_n; ++i)
        for(size_t j = 0; j < col_n; ++j)
            m3[i][j] = m1.getRow(i) * m2.getCol(j);
    return m3;
}

