#include "Engine.h"

Engine::Engine() :
    m_FieldSize(36),
    m_Sound(),
    m_Font(),
    m_HighScore(m_FieldSize, m_Sound, m_Font),
    m_GridBorder(),
    m_GridPosition(234, 64),
    m_HoldEmpty(true),
    m_BackgroundSprite()

    //m_Preview(nullptr)
{
    m_Font.loadFromFile("MontserratAlternates-Bold.otf");
    m_ElapsedTime = sf::Time::Zero;
    m_GridBorder.setSize(sf::Vector2f(10 * m_FieldSize, 18 * m_FieldSize));
    m_GridBorder.setOutlineThickness(2.f);
    m_GridBorder.setOutlineColor(sf::Color::White);
    m_GridBorder.setPosition(m_GridPosition);
    m_GridBorder.setFillColor(sf::Color::Transparent);

    m_ScoreBorder.setSize(sf::Vector2f(4 * m_FieldSize, 6 * m_FieldSize));
    m_ScoreBorder.setOutlineThickness(5.f);
    m_ScoreBorder.setOutlineColor(sf::Color::White);
    m_ScoreBorder.setPosition(615, 64);
    m_ScoreBorder.setFillColor(sf::Color::Transparent);

    m_PreviewBorder.setSize(sf::Vector2f(4 * m_FieldSize, 6 * m_FieldSize));
    m_PreviewBorder.setOutlineThickness(5.f);
    m_PreviewBorder.setOutlineColor(sf::Color::White);
    m_PreviewBorder.setPosition(615, 320);
    m_PreviewBorder.setFillColor(sf::Color::Transparent);

    m_HoldBorder.setSize(sf::Vector2f(5 * m_FieldSize, 6 * m_FieldSize));
    m_HoldBorder.setOutlineThickness(5.f);
    m_HoldBorder.setOutlineColor(sf::Color::White);
    m_HoldBorder.setPosition(20, 64);
    m_HoldBorder.setFillColor(sf::Color::Transparent);

	m_Window.create(sf::VideoMode((20*m_FieldSize) + 100, (20*m_FieldSize)), "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("TetrisTextur2.png")) 
    {
        std::cout << "Engine::Engine() - could not load m_Texture\n";
    };
    m_Grid = std::make_unique<Grid>(sf::Vector2i{ 10, 18 }, m_FieldSize, *this, m_GridPosition);
    m_MenuWindow = std::make_unique<MenuWindow>(sf::Vector2f(m_GridPosition.x + m_FieldSize, m_GridPosition.y + m_FieldSize)
        , sf::Vector2f(m_Grid->GetWidth() - 64, m_FieldSize * 5), m_Font, m_Sound);

    if (!m_Background.loadFromFile("tetrisbackground1.png")) 
    {
        std::cout << "Engine::Engine() - could not load m_Background\n";
    };
    m_BackgroundSprite.setTexture(m_Background);
    m_BackgroundSprite.setPosition(m_GridPosition);

    //m_Grid->addBlock(0, m_Tetromino->getBlockPositions());
    createTetromino(); 
    
}

void Engine::start()
{
    Quit = false;
    sf::Clock clock;
    sf::Time time{ sf::Time::Zero };
    m_Sound.setBackgroundMusic();
    
    while (m_Window.isOpen() && Quit == false)
    {
        sf::Time fallSpeed{ sf::seconds(200.f / (200.f + (m_HighScore.getLvl() * (m_HighScore.getLvl() * 30.f)))) };
        time = clock.restart();
        m_ElapsedTime += time;
        events();

        //GameLoop
        if (!m_ShowMenu)
        {
            update(time);
            if (m_ElapsedTime > fallSpeed)
            {
                m_ElapsedTime = sf::Time::Zero;
                proceed(Movement::FallDown);
            }
        }
        render();
    }
    QuitText();
}

void Engine::QuitText() 
{
    std::cout << "Game over!" << std::endl;
}

void Engine::update(const sf::Time& gameTime)
{
    m_Grid->update(gameTime);
    m_HighScore.update(gameTime);
    if (!m_Tetromino) {
        createTetromino();
    }
}

void Engine::events()
{
    sf::Event Event;

    while (m_Window.pollEvent(Event)) {
        //Menu screen events
        if (m_ShowMenu)
        {
            m_MenuWindow->Events(Event, m_ShowMenu, m_Window);
        }
        else
        {
            //Game screen events
            switch (Event.type) {
            case sf::Event::Closed:
                m_Window.close();
                break;
            case sf::Event::KeyPressed:
                if (Event.key.code == sf::Keyboard::S)
                {
                    proceed(Movement::PressDown);
                }
                else if (Event.key.code == sf::Keyboard::A)
                {
                    proceed(Movement::Left);
                }
                else if (Event.key.code == sf::Keyboard::D)
                {
                    proceed(Movement::Right);
                }
                else if (Event.key.code == sf::Keyboard::W)
                {
                    bool collided = false;
                    while (!collided)
                    {
                        collided = proceed(Movement::HardDown);
                    }
                }
                else if (Event.key.code == sf::Keyboard::Space)
                {
                    rotate();
                }
                else if (Event.key.code == sf::Keyboard::Escape)
                {
                    m_ShowMenu = true;
                }
                else if (Event.key.code == sf::Keyboard::Tab)
                {
                    holdAndSwapTetromino();
                }
                else if (Event.key.code == sf::Keyboard::O)
                {
                    Quit = true;
                }
                break;
            }
        }
    }
}


void Engine::rotate() {
    if (!m_Tetromino) return;
    m_Tetromino->rotate();
    if (CollisionDetection(m_Tetromino->getBlockPositions())) {
        m_Tetromino->revertState();
    }
}

void Engine::render(){
    m_Window.clear(sf::Color::Black);
    m_Window.draw(m_BackgroundSprite);
    m_Grid->draw(m_Window);
    if (m_Tetromino) m_Window.draw(*m_Tetromino);
    m_HighScore.draw(m_Window);
    m_Window.draw(*m_Preview);
    m_Window.draw(m_GridBorder);
    m_Window.draw(m_ScoreBorder);
    m_Window.draw(m_PreviewBorder);
    m_Window.draw(m_HoldBorder);
    if (m_Hold)
    {
        m_Window.draw(*m_Hold);
    }
    if(m_ShowMenu) m_MenuWindow->Draw(m_Window);
    
    m_Window.display();
}

void Engine::createTetromino() 
{
    m_Tetromino.reset(new Tetromino{ m_Texture, m_TetroId, m_FieldSize, m_GridPosition});
    if (m_Grid->occupied(m_Tetromino->Tetromino::getBlockPositions())) 
    {
        m_Grid->clean();
        m_HighScore.reset();
    }
    
    m_TetroId = getRandomNumber(6);
    m_Preview.reset(new Tetromino{m_Texture, m_TetroId, m_FieldSize, m_GridPosition});
    m_Preview->setPosition(sf::Vector2i{ 11 * m_FieldSize, 8 * m_FieldSize });
    m_Swapped = false;
}

bool Engine::proceed(Movement move)
{
    bool collision = false;
    
    //Error checking
    if (!m_Tetromino)
    {
        return false;
        std::cout << "Error: NO tetromino in proceed loaded" << std::endl;
    }

    if (!CollisionDetection(m_Tetromino->FuturePos(move)))
    {
        m_Tetromino->direction(move);
        if (move == Movement::PressDown) m_HighScore.addScore(1);
        if (move == Movement::HardDown) m_HighScore.addScore(2);
    }
    else
    {
        if (move == Movement::FallDown || move == Movement::PressDown || move == Movement::HardDown)
        {
            m_Sound.setCollisionSound();
            int id = m_Tetromino->getId();
            m_Grid->addBlock(id, m_Tetromino->getBlockPositions());
            m_Tetromino.reset();
            m_HighScore.sumScore();
            collision = true;
        }   
    }
    return collision;
}

void Engine::holdAndSwapTetromino()
{
    sf::Vector2i pos = m_Tetromino->getPosition();
    if (m_HoldEmpty)
    {
        //sets hold tetromino to current
        m_Hold = std::make_shared<Tetromino>(*m_Tetromino);
        m_Hold->setPosition(sf::Vector2i{ m_FieldSize * -5, 34 });
        createTetromino();
        m_Tetromino->setPosition(pos);
        m_HoldEmpty = false;
    }
    else
    {
        if (!m_Swapped)
        {
            //swaps tetromino and hold
            auto temp = std::make_shared<Tetromino>(*m_Hold);
            temp->setPosition(pos);
            if (!CollisionDetection(temp->getBlockPositions()))
            {
                m_Hold = std::make_shared<Tetromino>(*m_Tetromino);
                m_Hold->setPosition(sf::Vector2i{ m_FieldSize * -5, 34 });
                m_Tetromino = temp;
                //m_Swapped for only 1 swap per collision
                m_Swapped = true;
            }
        }
    }
}

bool Engine::isOccupied(int x, int y)
{
    return m_Grid->getField(x, y)->m_Occupied;
}

bool Engine::CollisionDetection(std::array<sf::Vector2i, 4> block) 
{
    for (int i = 0; i < 4; ++i) {

        if (block[i].x < 0 || block[i].x > 9 || block[i].y > 17)
        {
            return true;
        }
        if (isOccupied(block[i].x, block[i].y)) {
            return true;
        }
    }
    return false;
}