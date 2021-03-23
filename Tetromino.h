#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <array>
#include "Movement.h"


class Tetromino : public sf::Drawable
{
private:
	int m_BlockId;
	const int m_FieldSize;
	sf::Vector2i m_Position;
	std::array<sf::Vector2i, 4> m_Block;
	mutable sf::Sprite m_Sprite;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
public:
	Tetromino(sf::Texture& texture, int id);
	void setPositionByFields(const sf::Vector2i& position);
	std::array<sf::Vector2i, 4> getBlockPositions() const;

	void direction(Movement move);
	void setPosition(const sf::Vector2i& position);
};

