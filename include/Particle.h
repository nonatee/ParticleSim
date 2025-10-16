// ParticleSim.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include "Vector.h"
#include "Grid.h"
#include <bitset>
#include "Constants.h"

struct Particle {
	Vector2D position;
	Vector2D velocity;
	float mass;
	float radius;
	int index;
	std::bitset<PARTICLE_NUM> doneCollisionVec;
	Particle(Vector2D position, Vector2D velocity, float mass, float radius, int index);
	void UpdatePosition(float deltaTime, ParticleGrid& grid);
	void CheckCollisionAndDo(ParticleGrid grid, std::vector<Particle>& particleVec, std::vector<Vector2D>& deltaVec, std::vector<Vector2D>& posGrid);
};

void DoCollision(Particle& particle1, Particle& particle2, std::vector<Vector2D>& deltaVec, std::vector<Vector2D>& posGrid);
