
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <array>
#include <unordered_map>
#include "Engine.h"
#include "Sound.h"

class Engine;
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

	Engine& m_Engine;
	sf::Vector2i m_Size;
	sf::Vector2f m_startPosition;
	std::vector<int> m_YRemoved;
	float m_ElapsedTime;
	bool m_RemoveBlocks;
	int m_FieldSize;
	
	//std::shared_ptr<Sound> m_Sound;
	int m_Width, m_Height;
	Sound m_Sound;

public:
	Grid(sf::Vector2i size, int blockSize, Engine& engine, sf::Vector2f startPosition);
	void addBlock(int id, std::array<sf::Vector2i, 4> block);
	void update(const sf::Time& gameTime);
	void draw(sf::RenderWindow& window);
	bool occupied(std::array<sf::Vector2i, 4> block);
	void clean();
	void markLinesToRemove();
	void removeLines();
	void blink();
	Field* getField(int x, int y);
	const int GetWidth();
	const int GetHeight();
};

