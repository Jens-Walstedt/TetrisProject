#include "Engine.h"

Engine::Engine() :
m_HighScore()
{
    m_ElapsedTime = sf::Time::Zero;
	m_Window.create(sf::VideoMode((10*36), (18*36)), "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("TetrisTextur.png")) {
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
        sf::Time fallSpeed{ sf::seconds(0.3f) };
        time = clock.restart();
        m_ElapsedTime += time;
        events();
        update(time);
        if (m_ElapsedTime > fallSpeed)
        {
            m_ElapsedTime = sf::Time::Zero;
            proceed(Movement::Down);
        }

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
            if(Event.key.code == sf::Keyboard::S)
            {
                proceed(Movement::SoftDown);
            }
            else if (Event.key.code == sf::Keyboard::A) 
            {
                proceed(Movement::Left);
            }
            else if (Event.key.code == sf::Keyboard::D) 
            {
                proceed(Movement::Right);
            }
            else if (Event.key.code == sf::Keyboard::Space) 
            {
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
    m_TetroId = getRandomNumber(6);
    m_Tetromino.reset(new Tetromino{ m_Texture, m_TetroId});
}

void Engine::proceed(Movement move)
{
    if (CollisionDetection(m_Tetromino->FuturePos(move))) 
    {
        m_Tetromino->direction(move);
        if (move == Movement::SoftDown) m_HighScore.addScore(1);
    }
    else
    {
        if (move == Movement::Down || move == Movement::SoftDown)
        {
            int id = m_Tetromino->getId();
            m_Grid->addBlock(id, m_Tetromino->getBlockPositions());
            m_Tetromino.reset(nullptr);
        }
    }

}

bool Engine::CollisionDetection(std::array<sf::Vector2i, 4> block){

    for (int i = 0; i < 4; ++i) {

        if (block[i].x < 0 || block[i].x > 9 || block[i].y > 17) {
            return false;
        } 

        if (isOccupied(block[i].x, block[i].y)) {
            return false;
        }

    }

    return true;

}

bool Engine::isOccupied(int x, int y) {
    return m_Grid->getField(x, y)->m_Occupied;
}
