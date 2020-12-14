#pragma once

namespace Khrysalis {
	struct Vector2 {
		float X, Y;

		Vector2(float x, float y) : X(x), Y(y) {}
		Vector2(float scalar) : X(scalar), Y(scalar) {}
		Vector2(const Vector2& other) : X(other.X), Y(other.Y) {}

		bool operator<(const Vector2& other);
		bool operator>(const Vector2& other);

		bool operator<=(const Vector2& other);
		bool operator>=(const Vector2& other);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		Vector2 operator+(const Vector2& other);
		Vector2 operator-(const Vector2& other);
		Vector2 operator/(const Vector2& other);
		Vector2 operator*(const Vector2& other);

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 Left;
		static const Vector2 Right;
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Infinity;
		static const Vector2 NegativeInfinity;
	};
}