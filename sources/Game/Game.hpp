#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "WorkingDirectory/WorkingDirectory.h"
#include "Window/Window.h"
#include "Input/Input.h"

#include "../VectorCollections/VectorCollections.h"

class Game
{
private:
    //My own toolkits
    Window window;
    WorkingDirectory workingDir;
    Input input;

    //sample of drawing something
    sf::Texture vikingTexture;
    sf::Sprite  vikingSprite;

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


