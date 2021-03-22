#include "Tetromino.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

//Private
//TODO: does it do anything?
void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i = 0; i < 4; i++)
    {
        m_Sprite.setPosition(m_Block[i].x * 18 + m_Position.x, m_Block[i].y + m_Position.y);
        target.draw(m_Sprite);
    }
}

//public
Tetromino::Tetromino(sf::Texture& texture, int id)
    : m_Id(id),
    m_FieldSize(18)
{
    //TODO: TEST m_Position only (erase)
    m_Position = (sf::Vector2i(3 * m_FieldSize, m_FieldSize));
    m_Sprite = sf::Sprite(texture, sf::IntRect{ (id % 7) * 18, 0, m_FieldSize, m_FieldSize});
    for (size_t i = 0; i < 4; i++)
    {
        m_Block[i].x = i;
        m_Block[i].y = 1;
    }
}

void Tetromino::setPositionByFields(const sf::Vector2i& position)
{
    m_Position.x = position.x * 18;
    m_Position.y = position.y * 18;
}

std::array<sf::Vector2i, 4> Tetromino::getBlockPositions() const
{
    std::array<sf::Vector2i, 4> blockPositions;
    for (size_t i = 0; i < 4; i++)
    {
        blockPositions[i].x = m_Block[i].x + m_Position.x;
        blockPositions[i].y = m_Block[i].y + m_Position.y;
    }
    return blockPositions;
}

void Tetromino::direction(Movement move)
{
    if (move == Movement::Left)
    {
        m_Position.x--;
    }
    else if (move == Movement::Right)
    {
        m_Position.x++;
    }
    else
    {
        m_Position.y++;
    }
}

void Tetromino::setPosition(const sf::Vector2i& position)
{
    m_Position = position;
}
