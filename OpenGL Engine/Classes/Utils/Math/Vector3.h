#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__

#include<iostream>

struct Vector3 {
	float x, y, z;
	Vector3();
	Vector3(float x, float y, float z = 0.0f);

	friend std::ostream& operator<<(std::ostream& out, const Vector3& data);

	float Length();
	Vector3& Normalize();

	Vector3& Add(const Vector3& other);
	Vector3& Subtract(const Vector3& other);
	Vector3& Multiply(const Vector3& other);
	Vector3& Divide(const Vector3& other);
	Vector3& Multiply(const float& other);
	Vector3& Divide(const float& other);

	friend Vector3 operator+(Vector3 left, const Vector3& other);
	friend Vector3 operator-(Vector3 left, const Vector3& other);
	friend Vector3 operator*(Vector3 left, const Vector3& other);
	friend Vector3 operator/(Vector3 left, const Vector3& other);
	friend Vector3 operator*(Vector3 left, const float& other);
	friend Vector3 operator/(Vector3 left, const float& other);

	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator/=(const Vector3& other);

	Vector3& operator*=(const float& other);
	Vector3& operator/=(const float& other);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
};

#endif //__VECTOR_3_H__