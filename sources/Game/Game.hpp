#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "WorkingDirectory/WorkingDirectory.hpp"
#include "Window/Window.hpp"
#include "Input/Input.hpp"

#include "../VectorCollections/VectorCollections.hpp"

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


