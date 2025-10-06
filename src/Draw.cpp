#include <SFML/Graphics.hpp>
#include <Particle.h>
#include "Constants.h"

void DrawParticle(sf::RenderWindow& window, Particle particle) {
	sf::CircleShape circle = sf::CircleShape::CircleShape(particle.radius/RADIUS_SCALE,EDGE_COUNT);
	circle.setPosition(particle.position.ToVector2f());
	window.draw(circle);
}