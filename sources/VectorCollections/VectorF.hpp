#pragma once

#include "nVector.hpp"
#include "math.h"


namespace DAM
{
    template <class value_t>
    class Vector2 : public nVector<value_t,2>
    {
        value_t _len;
        
        void  setUpProperties()
        {
            this->x.me = this;
            this->y.me = this;
            this->len.me = this;
        }
        value_t calculateLength()
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
        Vector2(value_t _x=0, value_t _y=0): nVector<value_t,2>({_x,_y})
        {
            setUpProperties();
            calculateLength();
        }
            
        Vector2(std::initializer_list<value_t> c): nVector<value_t,2>(c,2)
            {
                if(c.size() > 2) std::__throw_logic_error("");
                setUpProperties();
                calculateLength();
            }
    
    //CopyConstructor
        Vector2(const nVector<value_t>& copy_me): nVector<value_t,2>(copy_me)
            {
                if(copy_me.size() != 2) assert(false);
                setUpProperties();
                calculateLength();
            }
        
        Vector2(const nVector<value_t,2>& copy_me): nVector<value_t,2>(copy_me)
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


    template <class value_t>
    class Vector3: public nVector<value_t,3>
    {
        value_t _len;
        
        void  setUpProperties()
        {
            this->x.me = this;
            this->y.me = this;
            this->z.me = this;
            this->len.me = this;
        }
        value_t calculateLength()
        {
            _len = std::sqrt(*this * *this);
            return _len;
        }
    public:
    //Properties
        class 
        {   
            friend Vector3;
            Vector3* me;
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
            friend Vector3;
            Vector3* me;
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
            friend Vector3;
            Vector3* me;
            public:
                value_t& operator =(const value_t& z)
                {
                    me->arrayPointer[1] = z;
                    me->calculateLength();
                    return  me->arrayPointer[1];
                };
                operator value_t () const { return me->arrayPointer[1]; }
        }z;
        
        
        class
        {
            friend Vector3;
            Vector3* me;
            public:
                operator value_t () const {return me->_len;}
        }len;

    //Constructor
        Vector3(value_t _x=0, value_t _y=0, value_t _z = 0): nVector<value_t,3>({_x,_y,_z})
        {
            setUpProperties();
            calculateLength();
        }
            
        Vector3(std::initializer_list<value_t> c): nVector<value_t,3>(c,3)
            {
                if(c.size() > 3) std::__throw_logic_error("");
                setUpProperties();
                calculateLength();
            }
    
    //CopyConstructor
    
        //I want them to be backward compatible; 
        //But not recomend to mix and match Vec3 and nVec
        Vector3(const nVector<value_t>& copy_me): nVector<value_t,3>(copy_me)
            {
                if(copy_me.size() != 3) assert(false);
                setUpProperties();
                calculateLength();
            }
        
        Vector3(const nVector<value_t,3>& copy_me): nVector<value_t,3>(copy_me)
            {
                if(copy_me.size() != 3) assert(false);
                setUpProperties();
                calculateLength();
            }
    
    //Assign
        Vector3& operator=(const nVector<value_t>& assign_me)
        {
            if(assign_me.size() != 3) assert(false);
            std::copy(assign_me.begin(), assign_me.end(), this->begin());
            calculateLength();
        }
        Vector3& operator=(std::initializer_list<value_t> assign_me)
        {
            if(assign_me.size() != 3) assert(false);
            std::copy(assign_me.begin(), assign_me.end(), this->begin());
            calculateLength();
        }

    //Getter
        Vector3& normalize()
        {
            if(len != 0)
                (*this) = *this/len;
            return *this;
        }
        Vector3 getNormalized() const{
            if(len != 0)
                return *this/len;
            
            return *this;
        }

    };
    
    
    typedef Vector3<float>  Vector3f;
    typedef Vector3<int>    Vector3i;
    typedef Vector3<double> Vector3d;
    typedef Vector3<unsigned int> Vector3u;
}