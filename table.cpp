#include "table.hpp"

Table::Table()
{
}

Table::Table(const sf::Vector2i& size, const sf::Texture& texture)
{
	this->size = size;
	this->texture = texture;
}

void Table::draw(sf::RenderWindow& window) const
{
	sf::VertexArray vertices(sf::Quads, 4);
	vertices[0].position = sf::Vector2f(0, 0);
	vertices[1].position = sf::Vector2f(size.x, 0);
	vertices[2].position = sf::Vector2f(size.x, size.y);
	vertices[3].position = sf::Vector2f(0, size.y);

	sf::Vector2u texSize = texture.getSize();
	vertices[0].texCoords = sf::Vector2f(0, 0);
	vertices[1].texCoords = sf::Vector2f(texSize.x, 0);
	vertices[2].texCoords = sf::Vector2f(texSize);
	vertices[3].texCoords = sf::Vector2f(0, texSize.y);

	window.draw(vertices, &texture);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(size.x / 2, 0);
	line[1].position = sf::Vector2f(size.x / 2, size.y);

	line[0].color = sf::Color::Blue;
	line[1].color = sf::Color::Red;
	window.draw(line);
}

sf::Vector2i Table::getSize() const
{
	return size;
}
