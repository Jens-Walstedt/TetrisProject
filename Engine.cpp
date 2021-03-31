#include "Engine.h"

Engine::Engine() :
    m_FieldSize(36),
    m_Sound(),
    m_HighScore(m_FieldSize, m_Sound),
    m_GridBorder(),
    m_GridPosition(264, 64),
    m_HoldEmpty(true)

    //m_Preview(nullptr)
{
    m_ElapsedTime = sf::Time::Zero;
    m_GridBorder.setSize(sf::Vector2f(10 * m_FieldSize, 18 * m_FieldSize));
    m_GridBorder.setOutlineThickness(5.f);
    m_GridBorder.setOutlineColor(sf::Color::Black);
    m_GridBorder.setPosition(m_GridPosition);
    m_GridBorder.setFillColor(sf::Color::Transparent);

    m_ScoreBorder.setSize(sf::Vector2f(4 * m_FieldSize, 6 * m_FieldSize));
    m_ScoreBorder.setOutlineThickness(5.f);
    m_ScoreBorder.setOutlineColor(sf::Color::Blue);
    m_ScoreBorder.setPosition(650, 64);
    m_ScoreBorder.setFillColor(sf::Color::Transparent);

    m_PreviewBorder.setSize(sf::Vector2f(4 * m_FieldSize, 6 * m_FieldSize));
    m_PreviewBorder.setOutlineThickness(5.f);
    m_PreviewBorder.setOutlineColor(sf::Color::Red);
    m_PreviewBorder.setPosition(650, 320);
    m_PreviewBorder.setFillColor(sf::Color::Transparent);

    m_HoldBorder.setSize(sf::Vector2f(4 * m_FieldSize, 6 * m_FieldSize));
    m_HoldBorder.setOutlineThickness(5.f);
    m_HoldBorder.setOutlineColor(sf::Color::Magenta);
    m_HoldBorder.setPosition(104, 64);
    m_HoldBorder.setFillColor(sf::Color::Transparent);

	m_Window.create(sf::VideoMode((20*m_FieldSize) + 100, (20*m_FieldSize)), "Tetris", sf::Style::Default);
    if (!m_Texture.loadFromFile("TetrisTextur2.png")) {
        std::cout << "Game::Game() - could not load mTexture\n";
    };
    m_Grid = std::make_unique<Grid>(sf::Vector2i{ 10, 18 }, m_FieldSize, *this, m_GridPosition);
    m_MenuWindow = std::make_unique<MenuWindow>(sf::Vector2f(m_GridPosition.x + 32, m_GridPosition.y + 32)
        , sf::Vector2f(m_Grid->GetWidth() - 64, m_FieldSize * 5));
    //m_BackgroundSprite.setTexture(m_Texture);
    //m_Grid->addBlock(0, m_Tetromino->getBlockPositions());
    createTetromino(); 
    
}

void Engine::start()
{
    sf::Clock clock;
    sf::Time time{ sf::Time::Zero };
    m_Sound.setBackgroundMusic();
    //GameLoop
    while (m_Window.isOpen())
    {
        sf::Time fallSpeed{ sf::seconds(85.f / (85.f + (m_HighScore.getLvl() * (m_HighScore.getLvl() * 5.f)))) };
        time = clock.restart();
        m_ElapsedTime += time;
        events();
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
        if (m_ShowMenu)
        {
            m_MenuWindow->Events(Event, m_ShowMenu);
        }
        else
        {
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
    m_Window.clear(sf::Color::Green);
    m_Grid->draw(m_Window);
    if (m_Tetromino) m_Window.draw(*m_Tetromino);
    //m_Window.draw(m_BackgroundSprite);
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

void Engine::createTetromino() {

    m_Tetromino.reset(new Tetromino{ m_Texture, m_TetroId, m_FieldSize, m_GridPosition});

    if (m_Grid->occupied(m_Tetromino->Tetromino::getBlockPositions())) {
        m_Grid->clean();
        m_HighScore.reset();
    }
    
    m_TetroId = getRandomNumber(6);
    m_Preview.reset(new Tetromino{m_Texture, m_TetroId, m_FieldSize, m_GridPosition});
    m_Preview->setPosition(sf::Vector2i{ 11 * m_FieldSize, 8 * m_FieldSize });
    m_Swapped = false;
}

void Engine::proceed(Movement move)
{
    //Error checking
    if (!m_Tetromino)
    {
        std::cout << "Error: NO tetromino in proceed loaded" << std::endl;
    }

    if (!CollisionDetection(m_Tetromino->FuturePos(move))) 
    {
        m_Tetromino->direction(move);
        if (move == Movement::PressDown) m_HighScore.addScore(1);
    }
    else
    {
        if (move == Movement::FallDown || move == Movement::PressDown)
        {
            m_Sound.setCollisionSound();
            int id = m_Tetromino->getId();
            m_Grid->addBlock(id, m_Tetromino->getBlockPositions());
            m_Tetromino.reset();
            m_HighScore.sumScore();
        }
    }
}

void Engine::holdAndSwapTetromino()
{
    if (m_HoldEmpty)
    {
        //sets hold tetromino to current
        m_Hold = std::make_shared<Tetromino>(*m_Tetromino);

        m_Hold->setPosition(sf::Vector2i{ m_FieldSize * - 4, 64 });
        createTetromino();
        m_HoldEmpty = false;
    }
    else
    {
        if (!m_Swapped)
        {
            //swaps tetromino and hold
            auto temp = std::make_shared<Tetromino>(*m_Hold);
            sf::Vector2i pos = m_Tetromino->getPosition();
            temp->setPosition(pos);
            if (!CollisionDetection(temp->getBlockPositions()))
            {
                m_Hold = std::make_shared<Tetromino>(*m_Tetromino);
                m_Hold->setPosition(sf::Vector2i{ m_FieldSize * -4, 64 });
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