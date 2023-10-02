#include <iostream>
#include <iomanip>

#include "nVector.h"

class Matrix
{
    typedef int     size_t;
    typedef float   value_t;
    typedef nVector<value_t> col_t;
public:
    Matrix(size_t row_m, size_t col_n)
    {

    }

    Matrix(std::initializer_list<std::initializer_list<value_t>> c)
    {
        col_n = c.size();
        
        size_t maxRows = 0;
        for(size_t i = 0; i < c.size(); ++i)
        {
            if(c[i].size() > maxRows)
            {
                maxRows = c[i].size();
            }
        }

        row_m = maxRows;    

        vectorArray = new col_t[col_n];
        for(size_t i = 0; i < col_n; ++i){
            *(vectorArray+i) = new col_t(c.begin, c.end, row_m);
        }
    }
private:
    size_t row_m;
    size_t col_n;
    col_t*   vectorArray;
};