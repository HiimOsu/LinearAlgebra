#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "../Bitmask/Bitmask.hpp"
class Input
{
private:
    Bitmask thisFrameKeys;
    Bitmask lastFrameKeys;
public:
    enum class Key
    {
        None = 0,
        Left = 1,
        Right = 2,
        Up = 3,
        Down = 4,
        Esc = 5
    };
    
    bool IsPressed(Key keycode);

    bool IsKeyUp(Key keycode);

    bool IsKeyDown(Key keycode);

    bool IsAnyKeyPressed();

    void Update();
};



#endif