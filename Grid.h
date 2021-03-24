
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <array>
#include <unordered_map>

struct FieldInfo 
{
	FieldInfo(sf::Texture& texture, int id, int blockSize);
	sf::Sprite m_Sprite;
};

struct Field
{
	Field& operator=(const Field& field);
	bool m_Occupied = false;
	bool m_Visible = true;
	FieldInfo* m_Info = nullptr;
};

class Grid
{
private:
	int convert2D_to_1D(int x, int y);
	std::unordered_map<unsigned int, std::unique_ptr<Field>> m_Fields;
	std::unordered_map<unsigned int, std::unique_ptr<FieldInfo>> m_FieldInfos;

	sf::Vector2i m_Size;
	float m_ElapsedTime;
	bool m_RemoveBlocks;
	int m_BlockSize;

public:
	Grid(sf::Vector2i size, sf::Texture texture, int blockSize);
	void addBlock(int id, std::array<sf::Vector2i, 4> block);
	void update(const sf::Time& gameTime);
	void draw(sf::RenderWindow& window);
	Field* getField(int x, int y);
};

