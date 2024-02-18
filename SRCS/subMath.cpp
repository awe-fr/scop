#include "../headers/major.h"

mat4	rotate_z(float time, float degree_angle) {
	float angle_radians = degree_angle * M_PI / 180.0f;
	angle_radians *= time;

	mat4	matrix;

	matrix.data[0][0] = cos(angle_radians);
	matrix.data[0][1] = -sin(angle_radians);
	matrix.data[0][2] = 0;
	matrix.data[0][3] = 0;

	matrix.data[1][0] = sin(angle_radians);
	matrix.data[1][1] = cos(angle_radians);
	matrix.data[1][2] = 0;
	matrix.data[1][3] = 0;

	matrix.data[2][0] = 0;
	matrix.data[2][1] = 0;
	matrix.data[2][2] = 1;
	matrix.data[2][3] = 0;

	matrix.data[3][0] = 0;
	matrix.data[3][1] = 0;
	matrix.data[3][2] = 0;
	matrix.data[3][3] = 1;

	return matrix;
}

mat4	look_At(vec3 eye, vec3 center, vec3 up) {
	vec3 cal;
	cal.x = center.x - eye.x;
	cal.y = center.y - eye.y;
	cal.z = center.z - eye.z;

	vec3 f = normalize(cal);
    vec3 r = normalize(cross(up, f));
    vec3 u = cross(f, r);

	mat4	matrix;

    matrix.data[0][0] = r.x;
    matrix.data[0][1] = u.x;
    matrix.data[0][2] = -f.x;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = r.y;
    matrix.data[1][1] = u.y;
    matrix.data[1][2] = -f.x;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = r.z;
    matrix.data[2][1] = u.z;
    matrix.data[2][2] = -f.x;
    matrix.data[2][3] = 0;

    matrix.data[3][0] = -dot(r, eye);
    matrix.data[3][1] = -dot(u, eye);
    matrix.data[3][2] = dot(f, eye);
    matrix.data[3][3] = 1;

    return matrix;
}

vec3 cross(const vec3& a, const vec3& b) {
	vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

	result.x = -result.x;
    result.y = -result.y;
    result.z = -result.z;
    return result;
}

vec3 normalize(const vec3& v) {
	vec3 result;
    float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}

float dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

mat4	perspective(float FOV, float aspect, float zNear, float zFar) {
	float tanHalfFovy = std::tan((FOV * M_PI / 180.0f) / 2.0f);

	mat4	matrix;

    matrix.data[0][0] = 1.0f / (aspect * tanHalfFovy);
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = 1.0f / (tanHalfFovy);
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = -(zFar + zNear) / (zFar - zNear);;
    matrix.data[2][3] = -1;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    matrix.data[3][3] = 0;

	return matrix;
}

mat4    init_Base(float value) {
    mat4    matrix;

    matrix.data[0][0] = value;
    matrix.data[0][1] = 0;
    matrix.data[0][2] = 0;
    matrix.data[0][3] = 0;

    matrix.data[1][0] = 0;
    matrix.data[1][1] = value;
    matrix.data[1][2] = 0;
    matrix.data[1][3] = 0;

    matrix.data[2][0] = 0;
    matrix.data[2][1] = 0;
    matrix.data[2][2] = value;
    matrix.data[2][3] = 0;

    matrix.data[3][0] = 0;
    matrix.data[3][1] = 0;
    matrix.data[3][2] = 0;
    matrix.data[3][3] = value;

	return matrix;
}

// mat4    mvp(mat4 proj, mat4 view, mat4 model) {
//     mat4    matrix;


//     return matrix;
// }