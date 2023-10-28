#pragma once
#include <iostream>
#include <string>

#include "nVectorFunctions.h"

template <typename value_t>
class nVector{
private:
    typedef int size_t;
    size_t      n_Order;
    value_t*    arrayPointer;
    static const bool _debug = true;
    nVector()
    {
        n_Order = 0;
        arrayPointer = nullptr;
        std::cout << "\tError:\tnVector::Default Constructor is called, which indicates an error\n";
    }
public:

//Constructor

    nVector(size_t n_Order, value_t initial_value = 0){
        if(n_Order < 1) n_Order = 1; 
        this->n_Order = n_Order;
        arrayPointer = new value_t [n_Order];
        nVectorFunctions::InitializeArray<value_t>(arrayPointer, initial_value, n_Order);
        
        if(_debug)
            std::printf("Default Consturctor: %s (%i) \n", to_string().c_str(), n_Order);
    }
    

    
    nVector(std::initializer_list<value_t> c, size_t n_Order = 0){
        if(_debug)
        {
            std::cout << "[VAR] _debug address: " << &_debug << std::endl;
        }
        if(n_Order < c.size()) 
            n_Order = c.size();
        this->n_Order = n_Order;
        arrayPointer = nVectorFunctions::AllocateArray<value_t>(n_Order, 0);
        std::copy(c.begin(), c.end(), arrayPointer);
    }
    
//Big3
    nVector(const nVector<value_t>& copy_me){
        n_Order = copy_me.n_Order;
        arrayPointer = new value_t [n_Order];
        nVectorFunctions::CopyArray<value_t>(arrayPointer, copy_me.arrayPointer, n_Order);
        
        if(_debug)
            std::printf("Copy Consturctor:  %s (%i) \n", to_string().c_str() ,n_Order);
    }

    nVector<value_t> operator =(const nVector<value_t>& copy_me)
    {
        if(n_Order != copy_me.n_Order){
            n_Order = copy_me.n_Order;
            delete arrayPointer;
            arrayPointer = new value_t[n_Order];
        }

        nVectorFunctions::CopyArray<value_t>(arrayPointer, copy_me.arrayPointer, n_Order);
        if(_debug)
            std::printf("Assignment Operator:  %s (%i) \n", to_string().c_str() ,n_Order);
        return *this;
    } 

    ~nVector()
    {
        // std::printf("Destructor:  %s (%i) \n", to_string().c_str(),n_Order);

        if(arrayPointer) delete arrayPointer;
    }

//Modifier
    friend nVector<value_t> operator+(const nVector<value_t>& v1)
    {
        return v1;
    }

    friend nVector<value_t> operator+(const nVector<value_t>& v1,  const nVector<value_t>& v2)
    {
        return vector_addition(v1, v2);
    }

    friend nVector<value_t> operator*(const nVector<value_t>& v1, value_t scalar){
        return scalar_multiplication(v1, scalar);
    }
    
    friend nVector<value_t> operator*(value_t scalar, const nVector<value_t>& v1){
        return scalar_multiplication(v1, scalar);
    }

    friend nVector<value_t> operator*(const nVector<value_t>& v1,  const nVector<value_t>& v2)
    {
        return dot_product(v1,v2);
    }
    
    friend nVector<value_t> operator-(const nVector<value_t>& v1)
    {
        return scalar_multiplication(v1, -1);
    }
    
    friend nVector<value_t> operator-(const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        return vector_addition(v1, scalar_multiplication(v2, -1));
    }
    
    friend nVector<value_t> vector_addition(const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        if(v1.count() != v2.count()) return nVector<value_t>();
        nVector<value_t> v3(v1);
        for (size_t i = 0; i < v3.count(); i++)
        {
            if(nVector<value_t>::_debug)
                std::cout << "i: " << i << " ,v1: " << v1[i] << ", v2: " << v2[i] << '\n';
            v3[i] += v2[i];
        }   
        return v3;
    }

    friend nVector<value_t> scalar_multiplication(const nVector<value_t>& v1, const value_t& scalar)
    {
        nVector<value_t> v3(v1);
        for (size_t i = 0; i < v3.count(); i++)
        {
            if(nVector<value_t>::_debug){
                std::cout << "i: " << i << " ,v1: " << v1[i] << "scalar: " << scalar << '\n';
            }
            v3[i] *= scalar;
        }
        return v3;

    }

    friend value_t dot_product(const nVector<value_t>& v1, const nVector<value_t>& v2)
    {
        if(v1.count() != v2.count()) return value_t();
        value_t value = 0;
        for(size_t i = 0; i < v1.count(); ++i){
            value += v1[i] * v2[i];
        }

        return value;
    }

//Getter
    value_t* begin()
    {
        return arrayPointer;
    }
    value_t* end()
    {
        return arrayPointer + n_Order;
    }
    size_t count() const
    {
        return n_Order;
    }

    value_t& operator [](size_t n){
        if(n < n_Order){
            return *(arrayPointer + n);
        }

        std::cout << "\tError:\tnVector::operator []\n";

        return *arrayPointer;
    }
    
    value_t& operator [](size_t n) const{
        if(n < n_Order){
            return *(arrayPointer + n);
        }

        std::cout << "\tError:\tnVector::operator []\n";

        return *arrayPointer;
    }

//String / Std output
  
    std::string to_string() const 
    {
        return nVectorFunctions::ToStringArray(arrayPointer, n_Order);
    }

    friend std::string to_string(const nVector<value_t>& object){
        return object.to_string();
    }
    
    friend std::ostream& operator<<(std::ostream& outs, const nVector<value_t>& v1)
    {
        outs << v1.to_string();
        return outs;
    }
  
};

template <typename value_t>
const bool nVector<value_t>::_debug;

