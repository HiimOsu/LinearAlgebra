#pragma once

#include "nVector.h"
#include "math.h"


namespace DAM
{
    class Vector2f : public nVector<float>
    {
        private:
            float len;
        public:
        //Constructor
            Vector2f(float x=0, float y=0): nVector<float>({x,y}) 
            {
                len = std::sqrt(*this * *this);
                // }
            }
            
            Vector2f(std::initializer_list<float> c): nVector<float>(c,2)
            {
                if(c.size() > 2) std::__throw_logic_error("");
                len = std::sqrt(*this * *this);
            }

            Vector2f(const nVector<float>& copy_me): nVector<float>(copy_me)
            {
                if(copy_me.size() != 2) assert(false);
                this->len = std::sqrt(*this * *this);
                
            }

        //Assign
            Vector2f& operator=(const nVector<float>& assign_me)
            {
                if(assign_me.size() != 2) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
                len = std::sqrt(assign_me*assign_me);
            }
            Vector2f& operator=(std::initializer_list<float> assign_me)
            {
                if(assign_me.size() != 2) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
                len = std::sqrt(*this * *this);
            }

        //Getter
            float& x() {return arrayPointer[0];}
            float& y() {return arrayPointer[1];}

            float length(){
                return len;
            }
            Vector2f normalize()
            {
                return *this/length();
            }

    };

    class Vector3f: public nVector<float>
    {
        private:
            float len;
        public:
            Vector3f(float x=0, float y=0, float z=0): nVector<float>({x,y,z}) 
            {
                len = std::sqrt(*this * *this);
            }
            
            Vector3f(std::initializer_list<float> c): nVector<float>(c,3)
            {
                if(c.size() > 3) std::__throw_logic_error("");
                len = std::sqrt(*this * *this);
            }

            //conversion from nVector to Vector3f
            Vector3f(const nVector<float>& copy_me): nVector<float>(copy_me)
            {
                if(copy_me.size() != 3) assert(false);
                len = std::sqrt(*this * *this);
            }

            //Assign
            Vector3f& operator=(const nVector<float>& assign_me)
            {
                if(assign_me.size() != 3) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
                len = std::sqrt(*this * *this);
            }
            
            Vector3f& operator=(std::initializer_list<float> assign_me)
            {
                if(assign_me.size() != 3) assert(false);
                std::copy(assign_me.begin(), assign_me.end(), begin());
                len = std::sqrt(*this * *this);
            }

            float& x() {return arrayPointer[0];}
            float& y() {return arrayPointer[1];}
            float& z() {return arrayPointer[2];}
            
            float length() const{
                return len;
            }
            Vector3f normalize() const
            {
                return *this/length();
            }
        // private:
        //     nVector<float> arr3;
    };

}