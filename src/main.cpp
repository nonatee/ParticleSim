#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <Draw.h>
#include <vector>
#include <random>
#include <unordered_set>
#include <Constants.h>
#include <bitset>
#include <fstream>

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(-1.0, 1.0); // Range [0.0, 1.0)
	float deltaTime = 0.0001;
	int time = 0;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::vector<Particle> particleVec{};
	std::vector<Vector2D> deltaVec{};
	std::vector<Vector2D> posVec{};
	particleVec.reserve(PARTICLE_NUM);
	deltaVec.resize(PARTICLE_NUM, Vector2D{ 0,0 });
	posVec.resize(PARTICLE_NUM, Vector2D{ 0,0 });
	sf::RenderWindow window;
	window.create(sf::VideoMode(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT)), "SFML Window");
	//particleVec.push_back(Particle(Vector2D(100, 100), Vector2D(1, 1), 10, 10, 0));
	//particleVec.push_back(Particle(Vector2D(200, 200), Vector2D(-1, -1), 10, 10, 1));
	for (int i = 0; i < PARTICLE_NUM; i++) {
		particleVec.push_back(Particle(Vector2D(400 + 400 * dist(gen), 400 + 400 * dist(gen)), Vector2D(100 * dist(gen), 100 * dist(gen)), 1, 5, i));
	}
	for (int j = 0; j <= particleVec.size() - 1; j++) {
		//particleVec.push_back(Particle(Vector2D(100, 100), Vector2D(1, 1), 10, 10, 0));
		deltaVec.push_back(Vector2D(0, 0));
		posVec.push_back(Vector2D(0, 0));
	}
	std::ofstream file("energy.csv");
	file << std::fixed << std::setprecision(6);
	while (window.isOpen()) {
		start = std::chrono::high_resolution_clock::now();
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
		for (int i = 0; i < PARTICLE_NUM; i++) {
			DrawParticle(window, particleVec[i]);
			particleVec[i].UpdatePosition(deltaTime, particleGrid);
		}
		for (int i = 0; i < PARTICLE_NUM; i++) {
			Particle& part = particleVec[i];
			part.CheckCollisionAndDo(particleGrid, particleVec,deltaVec,posVec);
			deltaVec[i] = deltaVec[i] + Vector2D(0, 1);
		}
		for (int i = 0; i < PARTICLE_NUM; i++) {
			particleVec[i].velocity = particleVec[i].velocity + deltaVec[i];
			particleVec[i].position = particleVec[i].position + posVec[i];
		}
		float energy = 0;
		for (int i = 0; i < PARTICLE_NUM; i++) {
			deltaVec[i] = Vector2D(0, 0);
			posVec[i] = Vector2D(0, 0);
			Particle& part = particleVec[i];
			part.doneCollisionVec.reset();
			energy += part.velocity.MagnitudeSquared();
		}
		//std::cout << energy << "\n" << time << "\n";
		for (auto& row : particleGrid)
			for (auto& cell : row)
				cell.clear();
		
		//file << time << ";" << energy << "\n";

		time++;
		window.display();
		window.clear();
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> duration = end - start;

		std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
	}
	file.close();
	return 0;
}
