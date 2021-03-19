#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <array>
#include "Movement.h"


class Tetromino : public sf::Drawable
{
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Vector2i m_Position;
    int m_Id;
    std::array<sf::Vector2i, 4> m_Block;
    mutable sf::Sprite m_Sprite;
public:
	Tetromino(sf::Texture& texture, int id);
	void setPositionByFields(const sf::Vector2i& position);
	std::array<sf::Vector2i, 4> getBlockPositions() const;

	void direction(Movement move);
	void setPosition(const sf::Vector2i& position);
};

