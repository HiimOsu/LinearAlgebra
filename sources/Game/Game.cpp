#include "Game.hpp"


Game::Game(): window("SFML GameEngine")
{
    // std::cout << "PATH::" << workingDir.Get() << "\n";

    vikingTexture.loadFromFile(workingDir.Get() + "Valkyrie.png");  	
	vikingSprite.setTexture(vikingTexture);
    deltaTime_sec = clock.restart().asSeconds();
    
    absoluteTime_sec = 0;
    every_i_sec = 0;
}

void Game::calculateDeltaTime()
{
    deltaTime_sec = clock.restart().asSeconds();

    absoluteTime_sec += deltaTime_sec;

}

bool Game::isRunning() const
{
    return window.isOpen();
}

void Game::CaptureInput()
{
    input.Update();

}

void Game::Update()
{
    window.Update();

    const float LIMIT = 1000;
    const float INCREMENT = 50;

    static float speed = 0;
    DAM::Vector2f dir(0,0);


    static DAM::Vector2f dis;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        if(speed < LIMIT)
            speed += INCREMENT * deltaTime_sec;

        DAM::Vector2f viking(vikingSprite.getPosition().x, vikingSprite.getPosition().y);
        DAM::Vector2f mouse(sf::Mouse::getPosition(window.getWindow()).x, sf::Mouse::getPosition(window.getWindow()).y);
        dis = viking - mouse;
        if(abs(dis.x) > 1)
        {
            if(dis.x < 0)
                dir.x = 1;
            if(dis.x > 0)
                dir.x = -1;
        }
        if(abs(dis.y) > 1)
        {
            if(dis.y < 0)
                dir.y = 1;
            if(dis.y > 0)
                dir.y = -1;
        }
    }
    else
    {
        
        if(speed < LIMIT)
            speed += INCREMENT * deltaTime_sec;
        if(!input.IsAnyKeyPressed())
            speed = 0;
        
        if(input.IsPressed(Input::Key::Up))
            dir.y = dir.y - 1;
        if(input.IsPressed(Input::Key::Down))
            dir.y = dir.y + 1;
        if(input.IsPressed(Input::Key::Left))
            dir.x = dir.x - 1;
        if(input.IsPressed(Input::Key::Right))
            dir.x = dir.x + 1;
        
    }

    dir.normalize();
    sf::Vector2f vik = vikingSprite.getPosition();

    vik.x += dir.x * speed * deltaTime_sec;
    vik.y += dir.y * speed * deltaTime_sec;

    vikingSprite.setPosition(vik);


    if(floor(absoluteTime_sec) > every_i_sec)
    {   
        every_i_sec++;
        if(every_i_sec % 5 == 0)
            std::cout   << "AbsTime: " << absoluteTime_sec << std::endl
                        << "ElapsedTime: " << deltaTime_sec << std::endl
                        << "Properties:\n"
                        << "    speed: " << speed << std::endl
                        << "    dir: " << dir << std::endl
                        << "    dis: " << dis << "\n\n";
    }
}

void Game::LateUpdate()
{
    
}

void Game::Draw()
{
    window.BeginDraw();

    window.Draw(vikingSprite);

    window.EndDraw();
}