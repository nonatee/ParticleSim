// ParticleSim.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "Vector.h"
struct Particle {
	Vector2D position;
	Vector2D velocity;
	float mass;
	float radius;
	Particle(Vector2D position, Vector2D velocity, float mass, float radius);
	void UpdatePosition(float deltaTime);
};

void DoCollision(Particle& particle1, Particle& particle2);
