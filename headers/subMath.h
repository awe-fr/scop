#pragma once

#include "./major.h"

struct	vec2 {
	float   x;
	float   y;
};

struct	vec3 {
	float	x;
	float	y;
	float	z;
};

struct	mat4 {
	float	data[4][4];
};

struct	UniformBufferObject	{
	mat4	model;
	mat4	view;
	mat4	proj;
};

mat4	rotate_z(float time, float degree_angle);
mat4	rotate_y(float time, float degree_angle);
mat4    rotate_x(float time, float degree_angle);
mat4	look_At(vec3 eye, vec3 center, vec3 up);
mat4	perspective(float FOV, float aspect, float zNear, float zFar);
mat4	init_Base(float value);
mat4    mat_multiplication(mat4 f, mat4 s);

vec3 cross(const vec3& a, const vec3& b);
vec3 normalize(const vec3& v);

float dot(const vec3& a, const vec3& b);