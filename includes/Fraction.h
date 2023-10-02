#include <iostream>

class fraction
{
public:
    fraction()
    {
        den = 1;
        num = 0;
        sign = pos;
    }

    fraction(float number)
    {
        
    }

    // operator + (frac, int/float/frac)
    // operator * (frac, int/float/frac)
    // operator / (frac, int/float/frac)
    // operator - (frac, int/float/frac)
    
private:
    enum sign_t
    {
        neg = 0,
        pos = 1
    };
    unsigned int num;
    unsigned int den;
    bool sign;
};


/*
    AND
    x1      x2   outcome
    pos     pos  pos
    neg     neg  neg
    pos     neg  neg
    neg     pos  neg
*/