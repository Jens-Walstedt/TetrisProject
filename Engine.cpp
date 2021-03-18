#include "Engine.h"
#include <iostream>

Engine::Engine()
{
	m_Window.create(sf::VideoMode{500, 500}, "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("Blocks.png")) {
        std::cout << "Game::Game() - could not load mTexture\n";
    };
    m_Grid = std::make_unique<Grid>(sf::Vector2i{ 10, 18 });
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
