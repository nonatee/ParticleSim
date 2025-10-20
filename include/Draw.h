#pragma once

#include <SFML/Graphics.hpp>
#include <Particle.h>

void DrawParticle(sf::RenderWindow& window, const Particle& particle);
void DrawHeatMap(sf::RenderWindow& window, const std::vector<Particle>& particleVec);