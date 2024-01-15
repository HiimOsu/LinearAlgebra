#ifndef BITMASK_H
#define BITMASK_H

#include <stdint.h>
#include <iostream>
#include <string>
class Bitmask
{
private:
   uint32_t mask;
public:
    Bitmask();

    void SetMask(Bitmask& other); 
	
	// Returns binary representation of bitmask.
    uint32_t GetMask() const; 
    
	// Returns true if bit at pos = 1, else false.
    bool GetBit(int pos) const; 
   
	// Sets bit at specified pos to 1 or 0 (true or false).
    void SetBit(int pos, bool on);
	
	// Sets bit at pos to 1.
    void SetBit(int pos); 
	
	// Sets bit at pos to 0.
    void ClearBit(int pos);
    
	// Sets all bits to 0.
    void Clear(); 

    // Return the bit masks in 1 and 0s
    std::string to_string();
};



#endif