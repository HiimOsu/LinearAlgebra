#pragma once
#include <iostream>
#include <string>

#include <cassert>

#include "nVectorFunctions.hpp"


//Defining "Gener Vector space" (10 Axioms) + Inner-ProductSpace (inner-product)

template <class value_t, int order = -1,     //-1 or <= 0 means no restricted order|| Fixed order of the ordered-pair
//Addition
void(*add)(value_t *destarr, const value_t* addarr, int count) = nVecFunc::addArray, 
    //Multiplication 
void(*mul)(value_t *destarr, value_t scalar, int count) = nVecFunc::mulArray, 
    //Negation
void (*neg)(value_t* destArr, int count)  = nVecFunc::negArray,
    //Inner-Product
value_t (*dot)(const value_t* Arr1, const value_t* Arr2, int count) = nVecFunc::dotArray
>
class nVector{

    void setNOrder(int __n_Order)
    {
        assert(__n_Order > 0 && "nVector Initializer Error");
        
        if(0 < order)
        {
            n_Order = order;
        }
        else if(order < __n_Order){
            this->n_Order = order;
        }
        else{
            this->n_Order = __n_Order;
        }
    }
protected:
    typedef int size_t;
    size_t      n_Order;
    value_t*    arrayPointer;
    static const bool _debug = false;
public:

//Constructor
    nVector()
    {
        n_Order = 0;
        arrayPointer=nullptr;
        if(_debug)
            std::cout << "\tWarning:\tnVector::Default Constructor is called, which should never be used\n";
    }
    nVector(size_t __n_Order, value_t initial_value = value_t()){
        setNOrder(__n_Order);
        arrayPointer = new value_t [n_Order];
        nVecFunc::InitializeArray<value_t>(arrayPointer, initial_value, n_Order);
        
        // if(_debug)
        //     std::printf("Default Consturctor: %s (%i) \n", to_string().c_str(), n_Order);
    }
    
    //to quickly initialize a vector                            
                                                    //Also can set the size of the order manually
    nVector(const std::initializer_list<value_t>& c, size_t __n_Order = order){

        //Fixed size nVector 
        if(order > 0)
        {
            if(c.size() > order) 
                assert(false 
                        && "Fixed_nVector(std::initializer_list<value_t> c)____ c.size > order");
            if(__n_Order != order)
                assert(false 
                    && "Fixed_nVector(std::initializer_list<value_t> c, n_order)___ setting order is not allowed");
            setNOrder(order);
        }
        //Set size by user
        else if(__n_Order > 0)
        {
            if(c.size() > __n_Order)
                std::cout << "Warning: nVector nVector(std::initializer_list<value_t> c, n_order) : \n"
                    << "\t\tList size is larger than cutom size, data will be lost\n";
            setNOrder(__n_Order);
        }
        //Size by the list
        else
            setNOrder(c.size());

        arrayPointer = nVecFunc::AllocateArray<value_t>(n_Order, value_t());
        std::copy(c.begin(), c.begin() + n_Order, arrayPointer);
    }
    nVector(const value_t* begin, const value_t* end)
    {
        setNOrder(end - begin);
        arrayPointer = new value_t[n_Order];
        std::copy(begin, begin + n_Order, arrayPointer);
    }
//Big4
    nVector(const nVector& copy_me){
        n_Order = copy_me.n_Order;
        arrayPointer = new value_t [n_Order];
        std::copy(copy_me.arrayPointer, copy_me.arrayPointer + n_Order , arrayPointer);

        // nVectorFunctions::CopyArray<value_t>(arrayPointer, copy_me.arrayPointer, n_Order);
        
        //I want to see if the value were correct the first place
        // if(_debug)
        //     std::printf("Copy Consturctor:  %s (%i) \n", to_string().c_str() ,n_Order);
    }

    nVector& operator =(const nVector& copy_me)
    {
        if(n_Order != copy_me.n_Order){
            assert(false && "nVector::operator =(const nVector&)____________Size != order");
            n_Order = copy_me.n_Order;
            delete arrayPointer;
            arrayPointer = new value_t[n_Order];
        }

        std::copy(copy_me.arrayPointer, copy_me.arrayPointer + n_Order , arrayPointer);
        // nVectorFunctions::CopyArray<value_t>(arrayPointer, copy_me.arrayPointer, n_Order);
        
        // if(_debug)
        //     std::printf("Assignment Operator:  %s (%i) \n", to_string().c_str() ,n_Order);
        return *this;
    } 
    
    ~nVector()
    {
        // std::printf("Destructor:  %s (%i) \n", to_string().c_str(),n_Order);

        if(arrayPointer) delete arrayPointer;
    }

    void swap(nVector& swap_me) throw()
    {
        std::swap(this->n_Order, swap_me.n_Order);
        std::swap(this->arrayPointer, swap_me.arrayPointer);
    }
//Assignment
    nVector& operator =(const std::initializer_list<value_t>& c)
    {
        if(c.size() != this->n_Order) assert(false && "nVector::operator =(const std::initializer_list<value_t>&)____________Size !=order");
        std::copy(c.begin(), c.end(), arrayPointer);
        return *this;
    } 


//Modifier
    //Warning It would change the size of the vector, Use it when you are constru
    value_t* changeOrder(const size_t& size)
    {
        if(order != -1) assert(false && "Error\t attempted to change the order of a nVector with a fixed size");
        value_t* temp_arr = new value_t[size];
        value_t* old_arr = arrayPointer;
        
        this->n_Order = size;

        if(old_arr)
            std::copy(old_arr, old_arr + size, temp_arr);
        arrayPointer = temp_arr;
        return old_arr;
    }

//Operator + - / *
    nVector& operator+=(const nVector& v2)
    {
        *this = (*this + v2);
        return *this;
    }
    nVector& operator-=(const nVector& v2)
    {
        // std::cout << "operator -=____this.debug():  " << this->debug_to_string() << std::endl;
        *this = (*this - v2);
        return *this;
    }

    nVector& operator*=(value_t scalar)
    {
        *this = *this *scalar;
        return *this;
    }
    nVector& operator/=(value_t scalar)
    {
        *this = *this /scalar;
        return *this;     
    }
 
    
    nVector operator+() const
    {
        return *this;
    }

    nVector operator+(const nVector& v2) const
    {
        return vecAdd(*this, v2);
    }

    nVector operator-() const
    {
        return vecNeg(*this);
    }
    
    nVector operator-(const nVector& v2) const
    {
        return vecAdd(*this, -v2);
    }
    
    nVector operator/(const value_t& scalar) const{
        return scalMul(*this, 1/scalar);
    }
    
    value_t operator* (const nVector& v2) const
    {
        return nVector::dotProduct(*this,v2);
    }
    
    nVector operator*(const value_t& scalar) const{
        return scalMul(*this, scalar);
    }
    
    friend nVector operator*(const value_t& scalar, const nVector& v1){
        return scalMul(v1, scalar);
    }
    
    value_t operator^(int exp) const
    {
        nVector<value_t, order, add,mul,neg,dot> v3(*this);
        for(int i = 0; i < exp; ++i)
            v3 *= *this;
        return v3;
    }

    bool operator ==(const nVector& v1) const
    {
        if(v1.n_Order != this->n_Order) 
            return false;

        for(int i = 0; i < v1.n_Order; ++i)
        {
            if(this->arrayPointer[i] != v1[i])
                return false;
        }
        return true;   
    }

//Primary operator
    static nVector vecAdd(const nVector& v1, const nVector& v2);

    static nVector scalMul(const nVector& v1, const value_t& scalar);
    
    static nVector vecNeg(const nVector&v1);

    static value_t dotProduct(const nVector& v1, const nVector& v2);
    

//Getter
    value_t* begin()
    {
        return arrayPointer;
    }
    value_t* end()
    {
        return arrayPointer + n_Order;
    }
    
    const value_t* begin() const
    {
        return arrayPointer;
    }
    const value_t* end() const
    {
        return arrayPointer + n_Order;
    }
    
    size_t size() const
    {
        return n_Order;
    }

    value_t& operator [](const size_t& n){
        if(n < n_Order){
            return *(arrayPointer + n);
        }

        std::cout << "\tError:\tnVector::operator []\n";
        assert(false);

        return *arrayPointer;
    }
    
    value_t& operator [](const size_t& n) const{
        if(n < n_Order){
            return *(arrayPointer + n);
        }
        std::cout << "\tError:\tnVector::operator []\n";

        assert(false);
        return *arrayPointer;
    }

//String / Std output
    std::string to_string() const
    {
        return nVecFunc::ToStringArray(arrayPointer, n_Order);
    }

    friend std::string to_string(const nVector& object){
        return object.to_string();
    }
    
    friend std::ostream& operator<<(std::ostream& outs, const nVector& v1)
    {
        outs << v1.to_string();
        return outs;
    }

    private:
    std::string debug_to_string() const {
        std::stringstream ss;
        ss << to_string() << "\t(" <<n_Order<< ")";
        return ss.str();
    }


};


template <class value_t,
int order,
void(*add)(value_t *destarr, const value_t* addarr, int count), 
void(*mul)(value_t *destarr, value_t scalar, int count), 
void (*neg)(value_t*,int),
value_t (*dot)(const value_t*, const value_t*,int)
>
value_t nVector<value_t, order, add,mul,neg,dot>::dotProduct(const nVector& v1, const nVector& v2) 
{
    if(v1.size() != v2.size()) 
        assert(false && "nVector______dotProduct, size doesn't match");
    // throw std::__throw_length_error("nVector<valueT>::dotProduct: v1.size != v2.size");
    // value_t value = 0;
    // for(size_t i = 0; i < v1.size(); ++i){
    //     value += v1[i] * v2[i];
    // }

    // return value;

    return dot(v1.arrayPointer, v2.arrayPointer, v1.size());
}

//VecAdd
template <class value_t,
int order,
void(*add)(value_t *, const value_t* , int ), 
void(*mul)(value_t *, value_t , int ), 
void (*neg)(value_t*,int),
value_t (*dot)(const value_t*, const value_t*,int)
>
nVector<value_t, order, add,mul,neg,dot> 
    nVector<value_t, order, add,mul,neg,dot>::vecAdd
        (const nVector& v1, const nVector& v2)
{
    if(v1.size() != v2.size())
    {
        // std::cout << "v1 : " << v1.size() << "  |  v2.size() : " << v2.size() << std::endl; 
        assert(false && "nVector::vecAdd____________v1.size != v2.size");
    }
    
    nVector<value_t, order, add,mul,neg,dot> v3(v1);
    add(v3.begin(), v2.begin(), v1.size());          
    return v3;
}

//ScalMul
template <class value_t,
int order,
void(*add)(value_t *, const value_t* , int ), 
void(*mul)(value_t *, value_t , int ), 
void (*neg)(value_t*,int),
value_t (*dot)(const value_t*, const value_t*,int)
>
nVector<value_t, order, add,mul,neg,dot>
    nVector<value_t, order, add,mul,neg,dot>::scalMul(const nVector& v1, const value_t& scalar)
{
    nVector<value_t, order, add,mul,neg,dot> v3(v1);

    mul(v3.begin(), scalar, v1.size());
    return v3;

}

//VecNeg
template <class value_t,
int order,
void(*add)(value_t *, const value_t* , int ), 
void(*mul)(value_t *, value_t r, int ), 
void (*neg)(value_t*,int),
value_t (*dot)(const value_t*, const value_t*,int)
>
nVector<value_t, order, add,mul,neg,dot> 
    nVector<value_t, order, add,mul,neg,dot>::vecNeg(const nVector&v1)
{
    nVector<value_t, order, add,mul,neg,dot> v3(v1);
    neg(v3.begin(), v3.size());
    return v3;
}

//Const Bool Debug
template <class value_t,
int order,
void(*add)(value_t *, const value_t* , int), 
void(*mul)(value_t *, value_t , int ), 
void (*neg)(value_t*,int),
value_t (*dot)(const value_t*, const value_t*,int)
>
const bool nVector<value_t, order, add,mul,neg,dot>::_debug;


