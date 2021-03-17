#pragma once
#include <SFML/Graphics.hpp>

class Engine
{
public:
	Engine();
	void start();

private:
	void update();
	void events();
	void render();
};

