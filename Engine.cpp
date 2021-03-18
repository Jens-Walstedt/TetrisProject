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
    //GameLoop
    while (m_Window.isOpen())
    {
        time = clock.restart();
        events();
        update(time);
        render();
    }
}

void Engine::update(const sf::Time& gameTime)
{
    
}

void Engine::events()
{

}

void Engine::render()
{
    m_Window.clear(sf::Color::Green);
    m_Grid->draw(m_Window);
}
