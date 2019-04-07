#pragma once

#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
public:
	vec3 A;
	vec3 B;

public:
	ray() {}
	ray(const vec3& a, const vec3& b) { A = a; B = b; }

	vec3 origin() const { return A; }								// 레이 시작점
	vec3 direction() const { return B; }							// 레이의 방향
	vec3 point_at_parameter(float t) const { return A + t * B; }	// 레이의 길이를 설정
};

#endif
