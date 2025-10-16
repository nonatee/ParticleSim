#include "Particle.h"
#include "Vector.h"
#include "Grid.h"
#include "Constants.h"
#include <iostream>
#include <unordered_map>

Particle::Particle(Vector2D position, Vector2D velocity, float mass, float radius, int index) :
	position(position),
	velocity(velocity),
	mass(mass),
	radius(radius),
	index(index){
};
	void Particle::UpdatePosition(float deltaTime ,ParticleGrid& grid) {
	
		position = position + velocity * deltaTime;
		int x = this->position.x / (GRID_SIZE);
		int y = this->position.y / (GRID_SIZE);
		if (!(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())) {
			return;
		}
			grid[x][y].push_back(this->index);
	}

static float GetNewVelocity(float velocity1, float velocity2, float mass1, float mass2) {
	return (2 * mass2 * velocity2 + velocity1 * (mass1 - mass2)) / (mass1 + mass2);
};

void DoCollision(Particle& p1, Particle& p2, std::vector<Vector2D>& deltaVec,std::vector<Vector2D>& posGrid) {
	Vector2D n = (p2.position - p1.position).Normalize();

	// Velocity components along normal
	float v1n = p1.velocity.DotProduct(n);
	float v2n = p2.velocity.DotProduct(n);

	// 1D elastic collision along the normal
	float newV1n = (v1n * (p1.mass - p2.mass) + 2 * p2.mass * v2n) / (p1.mass + p2.mass);
	float newV2n = (v2n * (p2.mass - p1.mass) + 2 * p1.mass * v1n) / (p1.mass + p2.mass);

	// Update velocities
	Vector2D v1nVec = n * newV1n;
	Vector2D v2nVec = n * newV2n;

	// Tangential component remains unchanged
	Vector2D v1tVec = p1.velocity - n * v1n;
	Vector2D v2tVec = p2.velocity - n * v2n;

	//p1.velocity = v1tVec + v1nVec;
	deltaVec[p1.index] = deltaVec[p1.index] + v1tVec + v1nVec - p1.velocity;
	deltaVec[p2.index] = deltaVec[p1.index] * - 1.0;
	p2.doneCollisionVec.set(p1.index, true);
	//std::cout << "did collision\n";
	posGrid[p1.index] = posGrid[p1.index] + n * 1 / 2 * -1.0;
	posGrid[p2.index] = posGrid[p2.index] + n * 1 / 2;

}

void Particle::CheckCollisionAndDo(ParticleGrid grid, std::vector<Particle>& particleVec, std::vector<Vector2D>& deltaVec, std::vector<Vector2D>& posGrid) {
	int xIndex = (this->position.x / (GRID_SIZE));
	int yIndex = (this->position.y / (GRID_SIZE));
	int default = -1;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
				int x = i + xIndex;
				int y = j + yIndex;
				if (!(x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size())) {
					continue;
				}
				for (int k = 0; k < grid[i + xIndex][j + yIndex].size(); k++) {
					Particle& part2 = particleVec[grid[i + xIndex][j + yIndex][k]];
					
					if (this->index == part2.index) {
						continue;
					}
					if (this->doneCollisionVec.test(part2.index)) {
						continue;
					}
					//std::cout << "checking";
					float dx = this->position.x - part2.position.x;
					float dy = this->position.y - part2.position.y;
					float rSum = this->radius + part2.radius;
					float rSumSq = rSum * rSum;
					if (((dx * dx) + (dy * dy)) < (rSumSq)) {
						
						DoCollision(*this, part2,deltaVec,posGrid);
					}
				}
		}
	}
	
	if (this->position.x - radius < 0) {
		Vector2D posXVec = Vector2D(-1, 0);
		Vector2D normalVec = posXVec * this->velocity.DotProduct(posXVec);
		deltaVec[this->index] = deltaVec[this->index] - normalVec * 2;
		posGrid[this->index] = posGrid[this->index] + Vector2D(radius - this->position.x,0);
	}
	if (this->position.x + 2*radius > 800) {
		Vector2D posXVec = Vector2D(1, 0);
		Vector2D normalVec = posXVec * this->velocity.DotProduct(posXVec);
		deltaVec[this->index] = deltaVec[this->index] - normalVec * 2;
		posGrid[this->index] = posGrid[this->index] + Vector2D((radius + this->position.x - SCREEN_WIDTH)/2, 0);
	}
	if (this->position.y - radius < 0) {
		Vector2D posXVec = Vector2D(0, -1);
		Vector2D normalVec = posXVec * this->velocity.DotProduct(posXVec);
		deltaVec[this->index] = deltaVec[this->index] - normalVec * 2;
		posGrid[this->index] = posGrid[this->index] + Vector2D(0,radius - this->position.y);
	}
	if (this->position.y + 2*radius > 800) {
		Vector2D posXVec = Vector2D(0, 1);
		Vector2D normalVec = posXVec * this->velocity.DotProduct(posXVec);
		deltaVec[this->index] = deltaVec[this->index] - normalVec * 2;
		posGrid[this->index] = posGrid[this->index] + Vector2D(0, (radius + this->position.y - SCREEN_HEIGHT)/2);
	}
}