#pragma once

#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class vec3 {
public:
	float e[3];

public:
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }									// +����
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }						// -����
	inline float operator[](int i) const { return e[i]; }									// ����[i]
	inline float& operator[](int i) { return e[i]; }										// &����[i]

	inline vec3& operator +=(const vec3 &v2);												// ���ͳ����� ����
	inline vec3& operator -=(const vec3 &v2);												// ���ͳ����� ����
	inline vec3& operator *=(const vec3 &v2);												// ���ͳ����� ����
	inline vec3& operator /=(const vec3 &v2);												// ���ͳ����� ������
	inline vec3& operator *=(const float t);												// ���Ϳ� ��Į���� ���� (���� * ��Į��, ��Į�� * ���� ��� �����ؾ���)
	inline vec3& operator /=(const float t);												// ���Ϳ� ��Į���� ������(���� / ��Į�� ����)

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }	// ������ ����		||v||
	inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; } // ������ ���� ����	||v||^2
	inline void make_unit_vector();															// ������ ����ȭ		(1 / ||v||) * v
};

// �Է� ��Ʈ��
inline istream& operator>>(istream &is, vec3 &t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

// ��� ��Ʈ��
inline ostream& operator<<(ostream &os, const vec3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

inline void vec3::make_unit_vector()
{
	float k = 1.0f / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	e[0] *= k;
	e[1] *= k;
	e[2] *= k;
}

// v1 + v2
inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

// v1 - v2
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

// v1 * v2
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

// v1 / v2
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

// t * v
inline vec3 operator*(float t, const vec3 &v)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

// v * t
inline vec3 operator*(const vec3 &v, float t)
{
	return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

// v / t
inline vec3 operator/(const vec3 &v, float t)
{
	return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

// v1, v2 ����
inline float dot(const vec3 &v1, const vec3 &v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

// v1, v2 ����
inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
		-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
		v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

// this += v
inline vec3& vec3::operator+=(const vec3 &v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];

	return *this;
}

// this *= v
inline vec3& vec3::operator*=(const vec3 &v)
{
	e[0] *= v.e[0];
	e[1] *= v.e[1];
	e[2] *= v.e[2];

	return *this;
}

// this /= v
inline vec3& vec3::operator/=(const vec3 &v)
{
	e[0] /= v.e[0];
	e[1] /= v.e[1];
	e[2] /= v.e[2];

	return *this;
}

// this -= v
inline vec3& vec3::operator-=(const vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];

	return *this;
}

// this *= t
inline vec3& vec3::operator*=(const float t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;

	return *this;
}

// this /= t
inline vec3& vec3::operator/=(const float t)
{
	float k = 1.0f / t;

	e[0] *= k;
	e[1] *= k;
	e[2] *= k;

	return *this;
}

// ����ȭ
inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

#endif
