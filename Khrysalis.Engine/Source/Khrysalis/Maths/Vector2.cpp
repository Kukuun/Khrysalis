#include "KalPch.h"
#include "Khrysalis/Maths/Vector2.h"

namespace Khrysalis {
	const Vector2 Vector2::Zero = Vector2(0, 0);
	const Vector2 Vector2::One = Vector2(1, 1);
	const Vector2 Vector2::Left = Vector2(1, 0);
	const Vector2 Vector2::Right = Vector2(-1, 0);
	const Vector2 Vector2::Up = Vector2(0, 1);
	const Vector2 Vector2::Down = Vector2(0, -1);
	const Vector2 Vector2::Infinity = Vector2(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	const Vector2 Vector2::NegativeInfinity = Vector2(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());

	bool Vector2::operator<(const Vector2& other) {
		return X < other.X && Y < other.Y;
	}

	bool Vector2::operator>(const Vector2& other) {
		return X > other.X && Y > other.Y;
	}

	bool Vector2::operator<=(const Vector2& other) {
		return X <= other.X && Y <= other.Y;
	}

	bool Vector2::operator>=(const Vector2& other) {
		return X >= other.X && Y >= other.Y;
	}

	bool Vector2::operator==(const Vector2& other) {
		return X == other.X && Y == other.Y;
	}

	bool Vector2::operator!=(const Vector2& other) {
		return X != other.X || Y != other.Y;
	}

	Vector2 Khrysalis::Vector2::operator+(const Vector2& other) {
		return Vector2(X + other.X, Y + other.Y);
	}

	Vector2 Khrysalis::Vector2::operator-(const Vector2& other) {
		return Vector2(X - other.X, Y - other.Y);
	}

	Vector2 Khrysalis::Vector2::operator/(const Vector2& other) {
		return Vector2(X / other.X, Y / other.Y);
	}

	Vector2 Khrysalis::Vector2::operator*(const Vector2& other) {
		return Vector2(X * other.X, Y * other.Y);
	}

	Vector2& Khrysalis::Vector2::operator+=(const Vector2& other) {
		X += other.X;
		Y += other.Y;

		return *this;
	}

	Vector2& Khrysalis::Vector2::operator-=(const Vector2& other) {
		X -= other.X;
		Y -= other.Y;

		return *this;
	}

	Vector2& Khrysalis::Vector2::operator/=(const Vector2& other) {
		X /= other.X;
		Y /= other.Y;

		return *this;
	}

	Vector2& Khrysalis::Vector2::operator*=(const Vector2& other) {
		X *= other.X;
		Y *= other.Y;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& vector) {
		return stream << "X: " << vector.X << ", Y: " << vector.Y << std::endl;
	}
}