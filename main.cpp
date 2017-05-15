#include <SFML/Graphics.hpp>
#include "game.hpp"

int main()
{
	sf::Vector2i size(700, 1000);
	std::string texName = "../data/table.jpg";
	Game game(size, texName, 0.1f, 0.001f);

	game.draw();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while(!game.isEnd())
	{
		sf::Event event;
		while(game.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				game.close();
			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::Q:
						game.close();
						break;
				}
			}
		}
	
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		if(timeSinceLastUpdate.asMilliseconds() > game.getUptime())
		{
			game.update();
			game.draw();
			clock.restart();
		}
	
	}
	
	
return 0;
}
