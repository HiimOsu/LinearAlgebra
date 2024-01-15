#pragma once

#include "nVector.h"
#include "math.h"


namespace DAM
{
    template <class value_t>
    class Vector2 : public nVector<value_t,2>
    {
        float _len;
        
        void  setUpProperties()
        {
            this->x.me = this;
            this->y.me = this;
            this->len.me = this;
        }
        float calculateLength()
        {
            _len = std::sqrt(*this * *this);
            return _len;
        }
    public:
    //Properties
        class 
        {   
            friend Vector2;
            Vector2* me;
            public:
                value_t& operator =(const value_t& x)
                {
                    me->arrayPointer[0] = x;
                    me->calculateLength();
                    return  me->arrayPointer[0];
                };
                operator value_t () const { return me->arrayPointer[0]; }
        }x;

        class
        {
            friend Vector2;
            Vector2* me;
            public:
                value_t& operator =(const value_t& y)
                {
                    me->arrayPointer[1] = y;
                    me->calculateLength();
                    return  me->arrayPointer[1];
                };
                operator value_t () const { return me->arrayPointer[1]; }
        }y;
        class
        {
            friend Vector2;
            Vector2* me;
            public:
                operator value_t () const {return me->_len;}
        }len;

    //Constructor
        Vector2(float _x=0, float _y=0): nVector<float,2>({_x,_y})
        {
            setUpProperties();
            calculateLength();
        }
            
        Vector2(std::initializer_list<value_t> c): nVector<float,2>(c,2)
            {
                if(c.size() > 2) std::__throw_logic_error("");
                setUpProperties();
                calculateLength();
            }
    
    //CopyConstructor
        Vector2(const nVector<value_t>& copy_me): nVector<float,2>(copy_me)
            {
                if(copy_me.size() != 2) assert(false);
                setUpProperties();
                calculateLength();
            }
        
        Vector2(const nVector<value_t,2>& copy_me): nVector<float,2>(copy_me)
            {
                if(copy_me.size() != 2) assert(false);
                setUpProperties();
                calculateLength();
            }
    
    //Assign
        Vector2& operator=(const nVector<value_t>& assign_me)
        {
            if(assign_me.size() != 2) assert(false);
            std::copy(assign_me.begin(), assign_me.end(), this->begin());
            calculateLength();
        }
        Vector2& operator=(std::initializer_list<value_t> assign_me)
        {
            if(assign_me.size() != 2) assert(false);
            std::copy(assign_me.begin(), assign_me.end(), this->begin());
            calculateLength();
        }

    //Getter
        Vector2& normalize()
        {
            if(len != 0)
                (*this) = *this/len;
            return *this;
        }
        Vector2 getNormalized() const{
            if(len != 0)
                return *this/len;
            
            return *this;
        }

    };

    typedef Vector2<float>  Vector2f;
    typedef Vector2<int>    Vector2i;
    typedef Vector2<double> Vector2d;
    typedef Vector2<unsigned int> Vector2u;

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