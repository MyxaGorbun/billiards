#include "game.hpp"

#include <algorithm>
#include <math.h>

Game::Game(sf::Vector2i& size, std::string texFileName, float uptime, float dec)
{
	window.create(sf::VideoMode(size.x, size.y), "Billiards");

	sf::Texture texture;
	if(!texture.loadFromFile(texFileName))
	{
		std::cout << "Can't load texture\"" << texFileName << "\"" << std::endl;
		close();
	}
	
	table = Table(size, texture);

	createBalls();

	this->uptime = uptime;
	deceleration = dec;

	end = false;
}

bool Game::pollEvent(sf::Event& event)
{
	return window.pollEvent(event);
}

void Game::draw()
{
	window.clear();
	table.draw(window);
	sf::Vector2f shift(0, 0);
	for(std::vector<Ball>::iterator ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
	{
		ballIt->draw(window, shift);
	}
	window.display();
}

void Game::update()
{
	for(std::vector<Ball>::iterator ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
	{
		ballIt->update(uptime, deceleration);
	}

	for(std::vector<Ball>::iterator ballIt = balls.begin(); ballIt != balls.end(); ++ballIt)
	{
		for(std::vector<Ball>::iterator ballIt2 = balls.begin(); ballIt2 != balls.end(); ++ ballIt2)
		{
			if(ballIt != ballIt2 && isCollision(*ballIt, *ballIt2))
			{
				makeCollision(*ballIt, *ballIt2);
			}
		}
	}
}

bool Game::isEnd()
{
	return end;
}

void Game::close()
{
	end = true;
	window.close();
}

void Game::createBalls()
{
	float radius;
	radius = 30;

	sf::Color colors[] = {sf::Color(255, 0, 0), sf::Color(0, 255, 0), sf::Color(0, 0, 255),
						  sf::Color(255, 255, 0), sf::Color(255, 0 , 255), sf::Color(0, 255, 255),
						  sf::Color(255, 128, 128), sf::Color(128, 255, 128), sf::Color(128, 128, 255),
						  sf::Color(0, 0, 0)};
	std::random_shuffle(&colors[0], &colors[9]);

	sf::Vector2i tableSize = table.getSize();

	sf::Vector2f position;

	int colorNum = 0;
	for(int i = 0; i < 4; ++i)
	{
		for(int col = 0; col <= i; ++col)
		{
			sf::Vector2f shift;
			shift.x = (radius + 1) * (col * 2 - i - 1) ;
			shift.y = -sqrtf(3) * i * (radius + 1);
			position = sf::Vector2f(tableSize.x / 2 + shift.x, tableSize.y / 3 + shift.y);
			balls.push_back(Ball(position, radius, colors[colorNum++]));
		}
	}
	position = sf::Vector2f(tableSize.x / 2 - radius, tableSize.y * 2 / 3);
	balls.push_back(Ball(position, radius, sf::Color::White, sf::Vector2f(0, -1)));
}

float Game::getUptime() const
{
	return uptime;
}
