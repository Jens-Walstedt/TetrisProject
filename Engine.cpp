#include "Engine.h"
#include <iostream>

Engine::Engine()
{
    m_ElapsedTime = sf::Time::Zero;
	m_Window.create(sf::VideoMode(500, 500), "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("Blocks.png")) {
        std::cout << "Game::Game() - could not load mTexture\n";
    };
    m_Grid = std::make_unique<Grid>(sf::Vector2i{ 10, 18 });
      
    m_BackgroundSprite.setTexture(m_Texture);
}

void Engine::start()
{
    sf::Clock clock;
    sf::Time time{ sf::Time::Zero };
    //GameLoop
    while (m_Window.isOpen())
    {
        time = clock.restart();
        m_ElapsedTime += time;
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

    sf::Event Event;

    while (m_Window.pollEvent(Event)) {
        
        switch (Event.type) {
        case sf::Event::Closed:
            m_Window.close();
        case sf::Event::KeyPressed:
            if(Event.key.code == sf::Keyboard::S){
                proceed(Direction::SoftDown);
            }else if (Event.key.code == sf::Keyboard::A) {
                proceed(Direction::Right);
            }else if (Event.key.code == sf::Keyboard::D) {
                proceed(Direction::Left);
            }else if (Event.key.code == sf::Keyboard::Space) {
                rotate();
            }else if (Event.key.code == sf::Keyboard::P) {
                m_Grid->printGrid();
            }else if (Event.key.code == sf::Keyboard::I) {
                m_HighScore.addClearedLines(10);
            }

        }

    }

}

void Engine::render()
{
    m_Window.clear(sf::Color::Green);
    //m_Grid->draw(m_Window);
    m_Window.draw(m_BackgroundSprite);
    m_Window.display();
}
