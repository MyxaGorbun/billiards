#include "balls.hpp"
#include <math.h>
#include <iostream>

Ball::Ball()
{
}

Ball::Ball(const sf::Vector2f& position, float radius, sf::Color color, sf::Vector2f velocity)
{
	this->position = position;
	this->radius = radius;
	this->color = color;
	this->velocity = velocity;
}

void Ball::update(float time, float deceleration)
{
//	position += velocity * time * (1.0f - deceleration);
	forces.push_back(-velocity * deceleration);
	sf::Vector2f resultant(0.f, 0.f);
	for(std::vector<sf::Vector2f>::iterator forceIt = forces.begin(); forceIt != forces.end(); ++forceIt)
	{
		resultant += *forceIt;
	}

	velocity += resultant * time;
	position += velocity * time;

	forces.clear();
}

void Ball::draw(sf::RenderWindow& window, sf::Vector2f& shift)
{
	sf::CircleShape shape(radius);
	shape.setFillColor(color);
	shape.setPosition(position + shift);
	window.draw(shape);
}

bool isCollision(const Ball& b1, const Ball& b2)
{
	return distance(b1.position, b2.position) < b1.radius + b2.radius;
}

float distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
	float x = v1.x - v2.x;
	float y = v1.y - v2.y;
	return sqrtf(x*x + y*y);
}

void makeCollision(Ball& b1, Ball& b2)
{
	float dist = distance(b1.position, b2.position);
	sf::Vector2f force = (b2.position - b1.position) * (b1.radius + b2.radius) / (dist * dist * 300);

	b1.addForce(-force);
	b2.addForce(force);
}

void Ball::addForce(const sf::Vector2f& force)
{
	forces.push_back(force);
}
