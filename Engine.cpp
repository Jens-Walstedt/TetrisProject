#include "Engine.h"
#include "Highscore.h"
#include <iostream>

Engine::Engine()
    : m_HighScore()
{
    m_ElapsedTime = sf::Time::Zero;
	m_Window.create(sf::VideoMode((10*18), (18*18)), "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("Blocks.png")) {
        std::cout << "Game::Game() - could not load mTexture\n";
    };
    m_Grid = std::make_unique<Grid>(sf::Vector2i{ 10, 18 }, m_Texture);
    
    //m_BackgroundSprite.setTexture(m_Texture);
    //m_Grid->addBlock(0, m_Tetromino->getBlockPositions());
    createTetromino(); 
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
    m_Grid->update(gameTime);
}

void Engine::events()
{

    sf::Event Event;

    while (m_Window.pollEvent(Event)) {
        
        switch (Event.type) {
        case sf::Event::Closed:
            m_Window.close();
            break;
        case sf::Event::KeyPressed:
            if(Event.key.code == sf::Keyboard::S){
                //proceed(Direction::SoftDown);
            }else if (Event.key.code == sf::Keyboard::A) {
                m_Tetromino->direction(Movement::Left);
            }else if (Event.key.code == sf::Keyboard::D) {
                m_Tetromino->direction(Movement::Right);
            }else if (Event.key.code == sf::Keyboard::Space) {
                //rotate();
            }
            break;
        }
    }
}

void Engine::render(){
    m_Window.clear(sf::Color::Green);
    m_Grid->draw(m_Window);
    if (m_Tetromino) m_Window.draw(*m_Tetromino);
    //m_Window.draw(m_BackgroundSprite);
    m_HighScore.draw(m_Window);
    m_Window.display();
}

void Engine::createTetromino() {
    //TODO add random number for id.
    m_Tetromino.reset(new Tetromino{ m_Texture, 5});
}
