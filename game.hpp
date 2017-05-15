#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "balls.hpp"
#include "table.hpp"

class Game
{
public:
	Game(sf::Vector2i& size, std::string texFileName, float uptime, float dec);

	void draw();
	void update();

	bool isEnd();
	void close();

	bool pollEvent(sf::Event& event);
	float getUptime() const;

private:
	void createBalls();

	float uptime;
	sf::RenderWindow window;
	std::vector<Ball> balls;
	Table table;
	
	float deceleration;

	bool end;
};
