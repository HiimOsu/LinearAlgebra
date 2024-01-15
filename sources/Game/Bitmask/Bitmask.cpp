#ifndef BITMASK_CPP
#define BITMASK_CPP

#include "Bitmask.hpp"

Bitmask::Bitmask()
{
    this->mask = 0;
}

void Bitmask::SetMask(Bitmask& other)
{
    this->mask = other.mask;
}   

// Returns binary representation of Bitmask.
uint32_t Bitmask::GetMask() const
{
    return mask;    
}

// Returns bit at pos.
bool Bitmask::GetBit(int pos) const
{
    return (this->mask & (1 << pos));
}   

// Sets bit at specified pos to 1 or 0 (true or false).
void Bitmask::SetBit(int pos, bool on)
{
    if(on)
        SetBit(pos);
    else 
        ClearBit(pos);
}

// Sets bit at pos to 1.
void Bitmask::SetBit(int pos)
{
    mask = this->mask | (1 << pos);
}

// Sets bit at pos to 0.
void Bitmask::ClearBit(int pos)
{
    mask = this->mask & ~(1 << pos);
}

// Sets all bits to 0.
void Bitmask::Clear()
{
    mask = 0;
}


std::string Bitmask::to_string()
{
    std::string str;

    str = std::to_string(GetBit(0));
    for(uint8_t i = 1; i < 32; ++i)
    {
        if(i % 4 == 0)
            str += " ";
        str += std::to_string(GetBit(i));
    }

    return str;
}


#endif