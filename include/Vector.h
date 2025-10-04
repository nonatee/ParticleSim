#pragma once

#include <cmath>

struct Vector2D {
	float x;
	float y;
	Vector2D();
	Vector2D(float x, float y);
	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(float scalar) const;
	Vector2D operator/(float scalar) const;
	float Magnitude() const;
	float MagnitudeSquared() const;
	Vector2D Normalize() const;
	float DotProduct(const Vector2D& other) const;
};