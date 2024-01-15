#include "Window.h"

Window::Window(const std::string& windowName) 
    : window(sf::VideoMode(800, 600), windowName, sf::Style::Titlebar)
{
    window.setVerticalSyncEnabled(true);    
    // window.setFramerateLimit(10);
}


void Window::Update()
{
    sf::Event evnet;
    if(window.pollEvent(evnet)){
        if(evnet.type == sf::Event::Closed)
            window.close();
    }

}

void Window::BeginDraw()
{
    window.clear();
}

void Window::Draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}  

void Window::EndDraw()
{
    window.display(); 
}


bool Window::isOpen() const
{
    return window.isOpen();
}
