#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Ball
{
public:
	Ball();
	Ball(const sf::Vector2f& position, float radius, sf::Color color, sf::Vector2f velocity = sf::Vector2f(0, 0));

	void update(float time, float deceleration);
	void addForce(const sf::Vector2f&);
	void draw(sf::RenderWindow& window, sf::Vector2f& shift);

	friend bool isCollision(const Ball&, const Ball&);
	friend void makeCollision(Ball&, Ball&);

private:
	sf::Color color;
	sf::Vector2f position;
	sf::Vector2f velocity;
	float radius;
	std::vector<sf::Vector2f> forces;
};


float distance(const sf::Vector2f&, const sf::Vector2f&);
