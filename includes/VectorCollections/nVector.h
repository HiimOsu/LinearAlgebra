#pragma once
#include <iostream>
#include <string>
#include <cassert>

#include "nVectorFunctions.h"

template <typename value_t>
class nVector{
protected:
    typedef int size_t;
    size_t      n_Order;
    value_t*    arrayPointer;
    static const bool _debug = false;
public:

//Constructor
    nVector() : nVector(1)
    {
        if(_debug)
            std::cout << "\tWarning:\tnVector::Default Constructor is called, which should never be used\n";
    }
    nVector(size_t n_Order, value_t initial_value = 0){
        if(n_Order < 1) n_Order = 1; 
        this->n_Order = n_Order;
        arrayPointer = new value_t [n_Order];
        nVecFunc::InitializeArray<value_t>(arrayPointer, initial_value, n_Order);
        
        // if(_debug)
        //     std::printf("Default Consturctor: %s (%i) \n", to_string().c_str(), n_Order);
    }
    nVector(const std::initializer_list<value_t>& c, size_t n_Order = -1){
        // if(_debug)
        // {
        //     std::cout << "[VAR] _debug address: " << &_debug << std::endl;
        // }
        
        if(n_Order < 0){
            n_Order = c.size();
        }
        else{
            if(c.size() > n_Order) assert(false && "nVector<value_t>::nVector(std::initializer_list<value_t> c)____________Size > order");
        } 

        this->n_Order = n_Order;
        arrayPointer = nVecFunc::AllocateArray<value_t>(n_Order, value_t());
        std::copy(c.begin(), c.begin() + n_Order, arrayPointer);
    }
    nVector(const value_t* begin, const value_t* end)
    {
        this->n_Order = end - begin;
        arrayPointer = new value_t[n_Order];
        std::copy(begin, end, arrayPointer);
    }
//Big3
    nVector(const nVector<value_t>& copy_me){
        n_Order = copy_me.n_Order;
        arrayPointer = new value_t [n_Order];
        std::copy(copy_me.arrayPointer, copy_me.arrayPointer + n_Order , arrayPointer);

        // nVectorFunctions::CopyArray<value_t>(arrayPointer, copy_me.arrayPointer, n_Order);
        
        //I want to see if the value were correct the first place
        // if(_debug)
        //     std::printf("Copy Consturctor:  %s (%i) \n", to_string().c_str() ,n_Order);
    }

    nVector<value_t>& operator =(const nVector<value_t>& copy_me)
    {
        if(n_Order != copy_me.n_Order){
            assert(false && "nVector<value_t>::operator =(const nVector<value_t>&)____________Size != order");
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
//Assignment
    nVector<value_t>& operator =(const std::initializer_list<value_t>& c)
    {
        if(c.size() != this->n_Order) assert(false && "nVector<value_t>::operator =(const std::initializer_list<value_t>&)____________Size !=order");
        std::copy(c.begin(), c.end(), arrayPointer);
        return *this;
    } 


//Modifier
    //Warning It would change the size of the vector, Use it when you are constru
    value_t* changeOrder(const size_t size)
    {
        value_t* temp_arr = new value_t[size], 
        *old_arr = arrayPointer;
        std::copy(arrayPointer, arrayPointer + size, temp_arr);
        arrayPointer = temp_arr;
        return old_arr;
    }
    friend nVector<value_t> operator+(const nVector<value_t>& v1)
    {
        return v1;
    }

    friend nVector<value_t> operator+(const nVector<value_t>& v1,  const nVector<value_t>& v2)
    {
        return vector_addition(v1, v2);
    }

    friend value_t operator* (const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        return nVector<value_t>::dot_product(v1,v2);
    }
    
    friend nVector<value_t> operator*(const nVector<value_t>& v1, const value_t& scalar){
        return scalar_multiplication(v1, scalar);
    }
    
    friend nVector<value_t> operator*(const value_t& scalar, const nVector<value_t>& v1){
        return scalar_multiplication(v1, scalar);
    }
    
    friend nVector<value_t> operator-(const nVector<value_t>& v1)
    {
        return scalar_multiplication(v1, -1);
    }
    
    friend nVector<value_t> operator/(const nVector<value_t>& v1, const value_t& scalar){
        return scalar_multiplication(v1, 1/scalar);
    }

    friend nVector<value_t> operator-(const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        return vector_addition(v1, scalar_multiplication(v2, -1));
    }
    
    friend nVector<value_t> vector_addition(const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        if(v1.size() != v2.size()) assert(false && "nVector::vector_addition____________v1.size != v2.size");
       
        nVector<value_t> v3(v1);
        nVecFunc::addArray(v3.begin(), v2.begin(), v1.size());          
        return v3;
    }

    friend nVector<value_t> scalar_multiplication(const nVector<value_t>& v1, const value_t& scalar)
    {
        nVector<value_t> v3(v1);

        nVecFunc::mulArray(v3.begin(), scalar, v1.size());
        return v3;

    }

    static value_t dot_product(const nVector<value_t>& v1, const nVector<value_t>& v2);
    

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

        return *arrayPointer;
    }
    
    value_t& operator [](const size_t& n) const{
        if(n < n_Order){
            return *(arrayPointer + n);
        }

        std::cout << "\tError:\tnVector::operator []\n";

        return *arrayPointer;
    }

//String / Std output
    std::string to_string() const
    {
        return nVecFunc::ToStringArray(arrayPointer, n_Order);
    }

    friend std::string to_string(const nVector<value_t>& object){
        return object.to_string();
    }
    
    friend std::ostream& operator<<(std::ostream& outs, const nVector<value_t>& v1)
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

template <class value_t>
value_t nVector<value_t>::dot_product(const nVector<value_t>& v1, const nVector<value_t>& v2) 
{
    if(v1.size() != v2.size()) 
        return value_t();
    // throw std::__throw_length_error("nVector<valueT>::dotProduct: v1.size != v2.size");
    value_t value = 0;
    for(size_t i = 0; i < v1.size(); ++i){
        value += v1[i] * v2[i];
    }

    return value;
}

template <typename value_t>
const bool nVector<value_t>::_debug;

