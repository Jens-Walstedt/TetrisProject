#include "Engine.h"
#include <iostream>
Engine::Engine()
{
	m_Window.create(sf::VideoMode{500, 500}, "Tetris", sf::Style::Default);
}

void Engine::start()
{
    sf::Clock clock;
    sf::Time time;
    while (m_Window.isOpen())
    {
        time = clock.restart();
        events();
        update();
        render();
    }
}

void Engine::update()
{
    
}

void Engine::events()
{

}

void Engine::render()
{

}
