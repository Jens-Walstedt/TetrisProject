#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include "Movement.h"

class Tetromino
{
private:
	void draw();
	sf::Vector2i m_Position;
	int m_CurrentRotation;
	int m_Id;

public:
	Tetromino(sf::Texture& texture, int id);
	~Tetromino() = default;

	void rotate();

	void direction(Movement move);
	void setPosition(const sf::Vector2i& position);
};

