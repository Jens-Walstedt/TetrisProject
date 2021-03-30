#include "Grid.h"
#include "Engine.h"
#include <iostream>

FieldInfo::FieldInfo(sf::Texture& texture, int id, int blockSize)
{
    sf::IntRect rect{ (id % 7) * blockSize, 0, blockSize, blockSize};
    m_Sprite.setTexture(texture);
    m_Sprite.setTextureRect(rect);
}

Field& Field::operator=(const Field& field)
{
    this->m_Occupied = field.m_Occupied;
    this->m_Visible = field.m_Visible;
    this->m_Info = field.m_Info;
    return *this;
}


Grid::Grid(sf::Vector2i size, int blockSize, Engine& engine, sf::Vector2f startPosition)
    : m_Size(size),
    m_FieldSize(blockSize),
    m_YRemoved(),
    m_Engine(engine),
    m_startPosition(startPosition)
{
    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            m_Fields[convert2D_to_1D(x, y)] = std::make_unique<Field>();
        }
    }

    for (int id = 0; id < 7; ++id) {
        m_FieldInfos[id] = std::make_unique<FieldInfo>(m_Engine.m_Texture, id, blockSize);
    }
}

void Grid::update(const sf::Time& gameTime)
{
    markLinesToRemove();
    if (m_RemoveBlocks)
    {
        m_ElapsedTime += gameTime.asSeconds();
        blink();
        if (m_ElapsedTime > 0.6f)
        {
            m_ElapsedTime = 0.f;
            removeLines();
        }
    }
}

void Grid::addBlock(int id, std::array<sf::Vector2i, 4> block) 
{
    for (int i = 0; i < 4; ++i) 
    {
        auto field = getField(block[i].x, block[i].y);
        field->m_Occupied = true;
        field->m_Info = m_FieldInfos[id].get();
    }
}

int Grid::convert2D_to_1D(int x, int y)
{
    return y * m_Size.x + x;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < m_Size.x; ++x) {
        for (int y = 0; y < m_Size.y; ++y) {
            auto field = getField(x, y);
            //if field has not been occupied yet, mInfo would be assigned to nullptr
            if (field->m_Occupied && field->m_Visible) {
                field->m_Info->m_Sprite.setPosition(x * (float)m_FieldSize + m_startPosition.x, y * (float)m_FieldSize + m_startPosition.y);
                window.draw(field->m_Info->m_Sprite);
            }
        }
    }
}

bool Grid::occupied(std::array<sf::Vector2i, 4> block)
{
    for (int i = 0; i < 4; i++)
    {
        auto field = getField(block[i].x, block[i].y);
        if (field->m_Occupied)
        {
            return true;
        }
    }
    return false;
}

void Grid::clean()
{
    for (int x = 0; x < m_Size.x; x++)
    {
        for (int y = 0; y < m_Size.y; y++)
        {
            auto field = getField(x, y);
            field->m_Occupied = false;
            field->m_Visible = true;
            field->m_Info = nullptr;
        }
    }
    
}

void Grid::markLinesToRemove()
{
    if (m_RemoveBlocks) return;

    int cntLinesCleared{ 0 };
    for (int y = m_Size.y - 1; y > 0; y--)
    {
        int cntr = 0;
        for (int x = 0; x < m_Size.x; x++)
        {
            auto field = getField(x, y);
            if (field->m_Occupied)
            {
                cntr++;
            }
            if (cntr == 10)
            {
                m_YRemoved.push_back(y);
                m_RemoveBlocks = true;
                cntLinesCleared++;
            }
        }
        cntr = 0;
    }
    m_Engine.m_HighScore.scoreSystem(cntLinesCleared);
    std::sort(m_YRemoved.begin(), m_YRemoved.end(), [](int left, int right) {return left < right; });
}

void Grid::removeLines()
{
    for (auto i : m_YRemoved)
    {
        for (auto y = i; y >= 0; y--)
        {
            for (auto x = 0; x < m_Size.x; x++)
            {
                int above = y - 1;
                if (above < 0) continue;
                *getField(x, y) = *getField(x, above);
            }
        }
    }
    m_Engine.m_Sound.setClearLineSound();
    m_YRemoved.clear();
    m_RemoveBlocks = false;
}

void Grid::blink()
{
    int num = int(m_ElapsedTime * 5.f);
    for (auto y : m_YRemoved)
    {
        for (int x = 0; x < m_Size.x; x++)
        {
            getField(x, y)->m_Visible = (num % 2 != 0);
        }
    }
}

Field* Grid::getField(int x, int y)
{
    return m_Fields[convert2D_to_1D(x, y)].get();
}
