
#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <array>
#include <unordered_map>

class Engine;

struct FieldInfo 
{
	FieldInfo(sf::Texture& texture, int id);
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
	
	void cleanLines();
	void markLinesRemoval();
	void blink();

	Engine& m_Engine;

	std::unordered_map<unsigned int, std::unique_ptr<Field>> m_Field;
	std::unordered_map<unsigned int, std::unique_ptr<FieldInfo>> m_FieldInfo;

	sf::Vector2i m_Size;
	std::vector<int> m_YCleaned;
	float m_ElapsedTime;
	bool m_RemoveBlocks;

public:
	Grid(sf::Vector2i size, Engine& engine);
	/*Grid(const Grid& other) = delete;
	Grid& operator =(const Grid& other) = delete;*/

	void update(const sf::Time& dt);
	//void clean();
	void addBlock(int id, std::array<sf::Vector2i, 4> block);
	bool occupied(std::array<sf::Vector2i, 4> block);
	void draw(sf::RenderWindow& window);
	void printGrid();
	//inline bool toRemoveBlocks() const { return m_RemoveBlocks; }
	//Field* getField{ int x, int y };

};

