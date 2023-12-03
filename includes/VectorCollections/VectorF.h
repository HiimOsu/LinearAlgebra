#pragma once

#include "nVector.h"
#include "math.h"

namespace DAM
{
    class Vector2f : public nVector<float>
    {
        private:

        public:
            Vector2f(float x=0, float y=0): nVector<float>({x,y}) 
            {
                // std::cout << n_Order << "\n";
                // for(int i = 0; i < n_Order; ++i)
                // {

                //     std::cout << *(arrayPointer+i) << std::endl;
                // }
            }
            
            Vector2f(std::initializer_list<float> c): nVector<float>(c,2)
            {
                if(c.size() > 2) std::__throw_logic_error("");
                
            }

            //Big3
            Vector2f(const nVector<float>& copy_me): nVector<float>(copy_me)
            {
                if(copy_me.size() != 2) assert(false);
            }

            //Assign
            Vector2f& operator=(const nVector<float>& assign_me)
            {
                if(assign_me.size() != 2) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
            }
            Vector2f& operator=(std::initializer_list<float> assign_me)
            {
                if(assign_me.size() != 2) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
            }

            float& x() {return arrayPointer[0];}
            float& y() {return arrayPointer[1];}
            
            float length(){
                return std::sqrt(Vector2f::dot_product(*this,*this));
            }
            Vector2f normalize()
            {
                return *this/length();
            }

    };

    class Vector3f: public nVector<float>
    {
        private:

        public:
            Vector3f(float x=0, float y=0, float z=0): nVector<float>({x,y,z}) 
            {
                // std::cout << n_Order << "\n";
                // for(int i = 0; i < n_Order; ++i)
                // {

                //     std::cout << *(arrayPointer+i) << std::endl;
                // }
            }
            
            Vector3f(std::initializer_list<float> c): nVector<float>(c,3)
            {
                if(c.size() > 3) std::__throw_logic_error("");
                
            }

            //CopyConstructor
            //conversion from nVector to Vector3f
            Vector3f(const nVector<float>& copy_me): nVector<float>(copy_me)
            {
                if(copy_me.size() != 3) assert(false);
            }

            //Assign
            Vector3f& operator=(const nVector<float>& assign_me)
            {
                if(assign_me.size() != 3) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
            }
            
            Vector3f& operator=(std::initializer_list<float> assign_me)
            {
                if(assign_me.size() != 3) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
            }

            float& x() {return arrayPointer[0];}
            float& y() {return arrayPointer[1];}
            float& z() {return arrayPointer[2];}
            
            float length() const{
                return std::sqrt(Vector3f::dot_product(*this,*this));
            }
            Vector3f normalize() const
            {
                return *this/length();
            }
        // private:
        //     nVector<float> arr3;
    };
}