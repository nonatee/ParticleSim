#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "Particle.h"
#include "Vector.h"

TEST_CASE("DoCollision updates velocities for head-on collision", "[DoCollision]") {
    Particle p1(Vector2D(0, 0), Vector2D(1, 0), 1.0f, 1.0f, 0);
    Particle p2(Vector2D(2, 0), Vector2D(-1, 0), 1.0f, 1.0f, 1);

    DoCollision(p1, p2);

    // For equal mass and opposite velocities, they should swap velocities
    REQUIRE(p1.velocity.x == Approx(-1.0f));
    REQUIRE(p1.velocity.y == Approx(0.0f));
}

TEST_CASE("DoCollision with zero velocity", "[DoCollision]") {
    Particle p1(Vector2D(0, 0), Vector2D(0, 0), 1.0f, 1.0f, 0);
    Particle p2(Vector2D(2, 0), Vector2D(0, 0), 1.0f, 1.0f, 1);

    DoCollision(p1, p2);

    REQUIRE(p1.velocity.x == Approx(0.0f));
    REQUIRE(p1.velocity.y == Approx(0.0f));
}

TEST_CASE("DoCollision with different masses", "[DoCollision]") {
    Particle p1(Vector2D(0, 0), Vector2D(2, 0), 2.0f, 1.0f, 0);
    Particle p2(Vector2D(2, 0), Vector2D(-1, 0), 1.0f, 1.0f, 1);

    DoCollision(p1, p2);

    // Check that velocities are updated and momentum is conserved
    float totalMomentumBefore = p1.mass * 2.0f + p2.mass * -1.0f;
    float totalMomentumAfter = p1.mass * p1.velocity.x + p2.mass * p2.velocity.x;
    REQUIRE(totalMomentumBefore == Approx(totalMomentumAfter));
}

TEST_CASE("DoCollision with overlapping positions", "[DoCollision]") {
    Particle p1(Vector2D(1, 1), Vector2D(1, 1), 1.0f, 1.0f, 0);
    Particle p2(Vector2D(1, 1), Vector2D(-1, -1), 1.0f, 1.0f, 1);

    DoCollision(p1, p2);

    // Should not produce NaN or inf
    REQUIRE(std::isfinite(p1.velocity.x));
    REQUIRE(std::isfinite(p1.velocity.y));
}