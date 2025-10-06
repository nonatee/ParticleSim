#include <cmath>

#include"Vector.h"
#include <SFML/System/Vector2.hpp>

Vector2D::Vector2D() : x(0), y(0) {};
	Vector2D::Vector2D(float x, float y) : x(x), y(y) {};
	Vector2D Vector2D::operator+(const Vector2D& other) const {
		return Vector2D(x + other.x, y + other.y);
	};
	Vector2D Vector2D::operator-(const Vector2D& other) const {
		return Vector2D(x - other.x, y - other.y);
	};
	Vector2D Vector2D::operator*(float scalar) const {
		return Vector2D(x * scalar, y * scalar);
	};
	Vector2D Vector2D::operator/(float scalar) const {
		return Vector2D(x / scalar, y / scalar);
	};
	float Vector2D::Magnitude() const {
		return std::sqrt(x * x + y * y);
	};
	float Vector2D::MagnitudeSquared() const {
		return x * x + y * y;
	};
	Vector2D Vector2D::Normalize() const {
		float mag = Magnitude();
		return (mag == 0) ? Vector2D(0, 0) : Vector2D(x / mag, y / mag);
	};
	float Vector2D::DotProduct(const Vector2D& other) const {
		return x * other.x + y * other.y;
	};
	sf::Vector2f Vector2D::ToVector2f() const {
		return sf::Vector2f(x, y);
	}
