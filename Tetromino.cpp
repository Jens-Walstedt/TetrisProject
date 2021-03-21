#include "Tetromino.h"

//Private
//void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
//{
//    for (size_t i = 0; i < 4; i++)
//    {
//        m_Sprite.setPosition(m_Block[i].x * 18 + m_Position.x, m_Block[i].y + m_Position.y);
//    }
//}

//public
//Tetromino::Tetromino(sf::Texture& texture, int id)
//{
//    id = 0;
//    m_Position = (sf::Vector2i(3, 0));
//    for (size_t i = 0; i < 4; i++)
//    {
//        m_Block[i].x = i;
//        m_Block[i].y = 1;
//    }
//       
//}

void Tetromino::setPositionByFields(const sf::Vector2i& position)
{
    m_Position.x = position.x * 18;
    m_Position.y = position.y * 18;
}

std::array<sf::Vector2i, 4> Tetromino::getBlockPositions() const
{
    return std::array<sf::Vector2i, 4>();
}
