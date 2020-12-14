#pragma once

namespace Khrysalis {
	struct Vector3 {
		float X, Y, Z;

		Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
		Vector3(float scalar) : X(scalar), Y(scalar), Z(scalar) {}
		Vector3(const Vector3& other) : X(other.X), Y(other.Y), Z(other.Z) {}

		bool operator<(const Vector3& other);
		bool operator>(const Vector3& other);

		bool operator<=(const Vector3& other);
		bool operator>=(const Vector3& other);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		Vector3 operator+(const Vector3& other);
		Vector3 operator-(const Vector3& other);
		Vector3 operator/(const Vector3& other);
		Vector3 operator*(const Vector3& other);

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);

		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);

		static const Vector3 Zero;
		static const Vector3 One;
		static const Vector3 Left;
		static const Vector3 Right;
		static const Vector3 Up;
		static const Vector3 Down;
		static const Vector3 Forward;
		static const Vector3 Backward;
		static const Vector3 Infinity;
		static const Vector3 NegativeInfinity;
	};
}