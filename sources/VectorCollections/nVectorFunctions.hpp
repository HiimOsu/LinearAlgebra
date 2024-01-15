#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace nVecFunc{

    template<typename value_t>
    void InitializeArray(value_t *arrayPointer, value_t init_value, int count)
    {
        for(value_t* walker = arrayPointer; walker != arrayPointer + count; ++walker)
            *walker = init_value;
    }

    template<typename value_t>
    void CopyArray(value_t* destArrayPointer, value_t* copyArrayPointer, int count){

        std::copy(copyArrayPointer, copyArrayPointer + count , destArrayPointer);
        // for (size_t i = 0; i < count; i++)
        // {
        //     *(destArrayPointer+i) = *(copyArrayPointer + i);
        // }
    }

    template<class value_t>
    std::string ToStringArray(value_t* arrayPointer, int count){
        std::stringstream ss;

        ss << "[";
        for (size_t i = 0; i < count; i++)
        {   
            ss << *(arrayPointer + i);
            if(i != count -1) ss << "\t";
        }
        ss << "]";   
        return ss.str();
    }

    template <class value_t>
    value_t* AllocateArray(size_t count, value_t init_value = value_t())
    {
        value_t* ptr = new value_t[count];
        InitializeArray(ptr, init_value, count);
        return ptr;
    }

    template <class value_t>
    void addArray(value_t *destarr, const value_t* addarr, int count)
    {
        for(int i = 0; i < count; ++i)
            destarr[i] += addarr[i];
    }
    
    template <class value_t>
    void mulArray(value_t *destarr, value_t scalar, int count)
    {
        for(int i = 0; i < count; ++i)
            destarr[i] *= scalar;
    }

    template <class value_t>
    void negArray(value_t * destArr, int count)
    {
        for(int i = 0; i < count; ++i)
            destArr[i] *= -1;
    }

//IDK: maybe let ppl to define innerproduct 
    template <class value_t>
    value_t dotArray(const value_t* arr1, const value_t* arr2, int count)
    {
        value_t value = 0;
        for(int i = 0; i < count; ++i){
            value += arr1[i] * arr2[i];
        }

        return value;
    }

    template <class value_t, int count>
    value_t dotArray(const value_t* arr1, const value_t* arr2)
    {
        value_t value = 0;
        for(int i = 0; i < count; ++i){
            value += arr1[i] * arr2[i];
        }

        return value;
    }

}
