#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "WorkingDirectory.h"
#include "Window.h"

#include "../VectorCollections/VectorCollections.h"
#include "Input.h"

class Game
{
private:
    Window window;
    WorkingDirectory workingDir;

    //sample of drawing something
    sf::Texture vikingTexture;
    sf::Sprite  vikingSprite;

    Input input;
    sf::Clock   clock;
    float       deltaTime_sec;
    double      absoluteTime_sec;
    uint32_t    every_i_sec;
public:
    Game();

    bool isRunning() const;

    void CaptureInput();
    void Update();
    void LateUpdate();
    void Draw();
    void calculateDeltaTime();
};


