#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
private:
   sf::RenderWindow window;
public:
    Window(const std::string& windowName);

    void Update();
    void BeginDraw();
    void Draw(const sf::Drawable& drawable);
    void EndDraw();
    
    bool isOpen() const;
    sf::Window& getWindow(){return window;}
};