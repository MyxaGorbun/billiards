#pragma once 

#include <SFML/Graphics.hpp>

class Table
{
public:
	Table();
	Table(const sf::Vector2i& size, const sf::Texture& texture);
	
	void draw(sf::RenderWindow& window) const;
	sf::Vector2i getSize() const;

private:
	sf::Vector2i size;
	sf::Texture texture;
};
