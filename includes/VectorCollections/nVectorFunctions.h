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
            ss << *(arrayPointer + i) << ", ";
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
    
    template <class value_t, class scal_t>
    void mulArray(value_t *destarr, scal_t scalar, int count)
    {
        for(int i = 0; i < count; ++i)
            destarr[i] *= scalar;
    }
    
}
