#include <SFML/Graphics.hpp>
#include <Particle.h>
#include "Constants.h"

void DrawParticle(sf::RenderWindow& window, const Particle& particle) {
	sf::CircleShape circle = sf::CircleShape::CircleShape(particle.radius/RADIUS_SCALE,EDGE_COUNT);
	circle.setPosition(particle.position.ToVector2f());
	window.draw(circle);
}

void DrawHeatMap(sf::RenderWindow& window, const std::vector<Particle>& particleVec) {
	int heatMap[SCREEN_WIDTH / HEAT_SIZE][SCREEN_HEIGHT / HEAT_SIZE];
	for (int i = 0; i < SCREEN_WIDTH / HEAT_SIZE; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / HEAT_SIZE; j++) {
			heatMap[i][j] = 0;
		}
	}
	for (int i = 0; i < SCREEN_WIDTH / HEAT_SIZE; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / HEAT_SIZE; j++) {
			for (int index = 0; index < PARTICLE_NUM; index++) {
				Particle part = particleVec[index];
				if (part.position.x > i * HEAT_SIZE && part.position.x < (i + 1) * HEAT_SIZE && part.position.y > j * HEAT_SIZE && part.position.y < (j + 1) * HEAT_SIZE) {
					heatMap[i][j]++;
				}
			}
		}
	}
	for (int i = 0; i < SCREEN_WIDTH / HEAT_SIZE; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / HEAT_SIZE; j++) {
			sf::RectangleShape rect(sf::Vector2f(HEAT_SIZE, HEAT_SIZE));
			rect.setPosition(sf::Vector2f(i * HEAT_SIZE, j * HEAT_SIZE));

			// RGBA -> A (alpha) controls transparency (0 = fully transparent, 255 = fully opaque)
			rect.setFillColor(sf::Color(heatMap[i][j]*100, 0, 0, 100)); // Red with ~40% opacity
			window.draw(rect);
		}
	}
}