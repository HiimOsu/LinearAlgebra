#ifndef INPUT_CPP
#define INPUT_CPP

#include "Input.hpp"

bool Input::IsPressed(Key keycode)
{
    return thisFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyUp(Key keycode)
{
    bool thisKey = thisFrameKeys.GetBit((int) keycode);
    bool lastKey = lastFrameKeys.GetBit((int) keycode);

    return lastKey && !thisKey;
}

bool Input::IsKeyDown(Key keycode)
{
    bool thisKey = thisFrameKeys.GetBit((int) keycode);
    bool lastKey = lastFrameKeys.GetBit((int) keycode);

    return thisKey && !lastKey;
}

bool Input::IsAnyKeyPressed()
{
    return !thisFrameKeys.GetBit(0);
}

void Input::Update()
{
    lastFrameKeys = thisFrameKeys;
    
    thisFrameKeys.Clear();
    //Up
    thisFrameKeys.SetBit((int)Input::Key::Up,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) );
    //Down
    thisFrameKeys.SetBit((int)Input::Key::Down,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) );
    //Left
    thisFrameKeys.SetBit((int)Input::Key::Left,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) );
    //Right
    thisFrameKeys.SetBit((int)Input::Key::Right,
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
        (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) );

    //Escape
    thisFrameKeys.SetBit((int)Key::Esc, 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));

    if (thisFrameKeys.GetMask() == 0)
    {
        thisFrameKeys.SetBit(0);
    }    
}


#endif