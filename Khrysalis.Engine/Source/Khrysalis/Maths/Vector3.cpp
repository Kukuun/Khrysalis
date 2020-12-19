#include "KalPch.h"
#include "Khrysalis/Maths/Vector3.h"

namespace Khrysalis {
	const Vector3 Vector3::Zero = Vector3(0, 0, 0);
	const Vector3 Vector3::One = Vector3(1, 1, 1);
	const Vector3 Vector3::Left = Vector3(1, 0, 0);
	const Vector3 Vector3::Right = Vector3(-1, 0, 0);
	const Vector3 Vector3::Up = Vector3(0, 1, 0);
	const Vector3 Vector3::Down = Vector3(0, -1, 0);
	const Vector3 Vector3::Forward = Vector3(0, 0, 1);
	const Vector3 Vector3::Backward = Vector3(0, 0, -1);
	const Vector3 Vector3::Infinity = Vector3(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	const Vector3 Vector3::NegativeInfinity = Vector3(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());

	bool Vector3::operator<(const Vector3& other) {
		return X < other.X && Y < other.Y && Z < other.Z;
	}

	bool Vector3::operator>(const Vector3& other) {
		return X > other.X && Y > other.Y && Z > other.Z;
	}

	bool Vector3::operator<=(const Vector3& other) {
		return X <= other.X && Y <= other.Y && Z <= other.Z;
	}

	bool Vector3::operator>=(const Vector3& other) {
		return X >= other.X && Y >= other.Y && Z >= other.Z;
	}

	bool Vector3::operator!=(const Vector3& other) {
		return X != other.X || Y != other.Y || Z != other.Z;
	}

	bool Vector3::operator==(const Vector3& other) {
		return X == other.X && Y == other.Y || Z == other.Z;
	}

	Vector3 Khrysalis::Vector3::operator+(const Vector3& other) {
		return Vector3(X + other.X, Y + other.Y, Z + other.Z);
	}

	Vector3 Khrysalis::Vector3::operator-(const Vector3& other) {
		return Vector3(X - other.X, Y - other.Y, Z - other.Z);
	}

	Vector3 Khrysalis::Vector3::operator/(const Vector3& other) {
		return Vector3(X / other.X, Y / other.Y, Z / other.Z);
	}

	Vector3 Khrysalis::Vector3::operator*(const Vector3& other) {
		return Vector3(X * other.X, Y * other.Y, Z * other.Z);
	}

	Vector3& Khrysalis::Vector3::operator+=(const Vector3& other) {
		X += other.X;
		Y += other.Y;
		Z += other.Z;

		return *this;
	}

	Vector3& Khrysalis::Vector3::operator-=(const Vector3& other) {
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;

		return *this;
	}

	Vector3& Khrysalis::Vector3::operator/=(const Vector3& other) {
		X /= other.X;
		Y /= other.Y;
		Z /= other.Z;

		return *this;
	}

	Vector3& Khrysalis::Vector3::operator*=(const Vector3& other) {
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3& vector) {
		return stream << "X: " << vector.X << ", Y: " << vector.Y << ", Z: " << vector.Z << std::endl;
	}
}