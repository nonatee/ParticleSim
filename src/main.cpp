#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <Draw.h>
#include <Constants.h>
int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "SFML Window");
	Particle part1 = Particle(Vector2D(100, 100), Vector2D(100, 100), 10, 100);
	
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
		}

		DrawParticle(window, part1);
		window.display();
		window.clear();
	}
	return 0;
}
