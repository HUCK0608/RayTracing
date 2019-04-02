#pragma once
#include <math.h>

class CVector3
{
public:
	float v[3];

public:
	CVector3();
	CVector3(float v0, float v1, float v2) { v[0] = v0; v[1] = v1; v[2] = v2; }
	~CVector3();

public:
	inline float x() const { return v[0]; }
	inline float y() const { return v[1]; }
	inline float z() const { return v[2]; }
	inline float r() const { return v[0]; }
	inline float g() const { return v[1]; }
	inline float b() const { return v[2]; }

public:
	inline const CVector3& operator+() const { return *this; }
	inline CVector3 operator-() const { return CVector3(-v[0], -v[1], -v[2]); }
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }

	inline CVector3& operator+=(const CVector3 &v2);
	inline CVector3& operator-=(const CVector3 &v2);
	inline CVector3& operator*=(const CVector3 &v2);
	inline CVector3& operator/=(const CVector3 &v2);
	inline CVector3& operator*=(const float t);
	inline CVector3& operator/=(const float t);

public:
	inline float length() const { return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }
	inline float squared_length() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	inline void make_unit_vector();
};

