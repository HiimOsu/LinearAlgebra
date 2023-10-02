#pragma once    
#include <iostream>
#include <string>
#include <sstream>


namespace nVectorFunctions{


    template<typename value_t>
    void InitializeArray(value_t *arrayPointer, value_t value, int count)
    {
        for(value_t* walker = arrayPointer; walker != arrayPointer + count; ++walker)
            *walker = value;
    }

    template<typename value_t>
    void CopyArray(value_t* destArrayPointer, value_t* copyArrayPointer, int count){
        for (size_t i = 0; i < count; i++)
        {
            *(destArrayPointer+i) = *(copyArrayPointer + i);
        }
    }

    template<class value_t>
    std::string ToStringArray(value_t* arrayPointer, int count){
        std::stringstream ss;
        for (size_t i = 0; i < count; i++)
        {   
            ss << std::to_string(*(arrayPointer + i)) << " ";
        }
        
        return ss.str();
    }
}