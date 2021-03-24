#include "Tetromino.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

/*
 * Block Shape 4 x 4
 *  [ 0   1     2   3]
 *  [ 4   5     6   7]
 *  [ 8   9     10  11]
 *  [ 12  13    14  15]
 * */

unsigned int BlockStorage[7][4] = {

        {4, 5,  8,  9},    // Square
        {5, 9, 13,  12},    // Reverse-L
        {5, 9, 10,  14},    // Z
        {5, 9,  8,  12},    // Reverse-Z
        {5, 8,  9,  10},    // T
        {5, 9,  13, 14},    // L
        {1, 5,  9,  13},    // I
};

//Private
void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (int i = 0; i < 4; i++)
    {
        m_Sprite.setPosition(m_Block[i].x * m_FieldSize + m_Position.x,
            m_Block[i].y * m_FieldSize + m_Position.y);
        target.draw(m_Sprite);
    }
}

//public
Tetromino::Tetromino(sf::Texture& texture, int blockId)
    : m_BlockId(blockId),
    m_FieldSize(36),
    m_Position(sf::Vector2i(3 * m_FieldSize, m_FieldSize)),
    m_Sprite(sf::Sprite(texture, sf::IntRect{ (blockId % 7) * m_FieldSize, 0, m_FieldSize, m_FieldSize }))
{    
    for (size_t i = 0; i < 4; ++i)
    {
        m_Block[i].x = BlockStorage[m_BlockId][i] % 4;
        m_Block[i].y = BlockStorage[m_BlockId][i] / 4;
    }
}

void Tetromino::setPositionByFields(const sf::Vector2i& position)
{
    m_Position.x = position.x * m_FieldSize;
    m_Position.y = position.y * m_FieldSize;
}

std::array<sf::Vector2i, 4> Tetromino::getBlockPositions() const
{
    std::array<sf::Vector2i, 4> blockPositions;
    for (int i = 0; i < 4; i++)
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
        m_Position.x -= m_FieldSize;
    }
    else if (move == Movement::Right)
    {
        m_Position.x += m_FieldSize;
    }
    else
    {
        m_Position.y += m_FieldSize;
    }
}

void Tetromino::setPosition(const sf::Vector2i& position)
{
    m_Position = position;
}

std::array<sf::Vector2i, 4> Tetromino::FuturePos(Movement direction) const {

    std::array<sf::Vector2i, 4> blockPositions;
    sf::Vector2i tempPosition{m_Position};

    if (direction == Movement::Left) {
        tempPosition.x--;
    } else if (direction == Movement::Right) {
        tempPosition.x++;
    } else {
        tempPosition.y++;
    }

    for (auto i = 0; i < 4; ++i) {
        blockPositions[i] = sf::Vector2i{ m_Block[i].x + tempPosition.x, m_Block[i].y + tempPosition.y };
    }

    return blockPositions;

}
