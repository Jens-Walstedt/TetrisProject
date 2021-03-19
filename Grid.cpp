#include "Grid.h"

FieldInfo::FieldInfo(sf::Texture& texture, int id)
{
    sf::IntRect rect{ (id % 7) * 18, 0, 18,18 };
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


Grid::Grid(sf::Vector2i size)
{
    for (int x = 0; x < size.x; ++x) {
        for (int y = 0; y < size.y; ++y) {
            m_Fields[convert2D_to_1D(x, y)] = std::make_unique<Field>();
        }
    }
}

void Grid::update(const sf::Time& gameTime)
{

}

//void Grid::addBlock(int id, std::array<sf::Vector2i, 4> block)
//{
//
//}

int Grid::convert2D_to_1D(int x, int y)
{
    return y * m_Size.x + x;
}

void Grid::draw(sf::RenderWindow& window)
{

}
