#include "Particle.h"
#include "Vector.h"

Particle::Particle(Vector2D position, Vector2D velocity, float mass, float radius) :
	position(position),
	velocity(velocity),
	mass(mass),
	radius(radius) {
};
void Particle::UpdatePosition(float deltaTime) {
	position = position + velocity * deltaTime;
}

float GetNewVelocity(float velocity1, float velocity2, float mass1, float mass2) {
	return (2 * mass2 * velocity2 + velocity1 * (mass1 - mass2)) / (mass1 + mass2);
};

void DoCollision(Particle& particle1, Particle& particle2) {
	Vector2D vecfrom1 = particle2.position - particle1.position.Normalize();
	Vector2D vel1projection = vecfrom1*particle1.velocity.DotProduct(vecfrom1);
	Vector2D vel2projection = vecfrom1*particle2.velocity.DotProduct(vecfrom1);
	Vector2D vel1orthogonal = particle1.velocity - vel1projection;
	Vector2D vel2orthogonal = particle2.velocity - vel2projection;
	particle1.velocity = vel1orthogonal + vecfrom1 * GetNewVelocity(
		vel1projection.Magnitude(),
		vel2projection.Magnitude(),
		particle1.mass,
		particle2.mass);
	particle2.velocity = vel2orthogonal + vecfrom1 * GetNewVelocity(
		vel2projection.Magnitude(),
		vel1projection.Magnitude(),
		particle2.mass,
		particle1.mass);
};
