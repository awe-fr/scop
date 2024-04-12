#include "../headers/major.hpp"

mat4	swp_mat(mat4 m)
{
	mat4	o;

	for (int y = 0; y < 4; ++y)
		for (int x = 0; x < 4; ++x)
			o.data[x][y] = m.data[y][x];
	return (m);
}

void	populate(float buf[16], mat4 m)
{
	for (int y = 0; y < 4; ++y)
		for (int x = 0; x < 4; ++x)
			buf[4 * y + x] = m.data[x][y];
}

mat4	rotate_z(float time, float degree_angle) {
	float angle_radians = degree_angle * M_PI / 180.0f;
	angle_radians *= time;

	mat4	matrix = init_Base(0);

	matrix.data[0][0] = cos(angle_radians);
	matrix.data[0][1] = -sin(angle_radians);

	matrix.data[1][0] = sin(angle_radians);
	matrix.data[1][1] = cos(angle_radians);

	matrix.data[2][2] = 1;

	matrix.data[3][3] = 1;

	return matrix;
}

mat4    rotate_y(float time, float degree_angle) {
    float angle_radians = degree_angle * M_PI / 180.0f;
    angle_radians *= time;

    mat4 matrix = init_Base(0);

    matrix.data[0][0] = cos(angle_radians);
    matrix.data[0][2] = sin(angle_radians);

    matrix.data[1][1] = 1;

    matrix.data[2][0] = -sin(angle_radians);
    matrix.data[2][2] = cos(angle_radians);

    matrix.data[3][3] = 1;

    return matrix;
}

mat4    rotate_x(float time, float degree_angle) {
    float angle_radians = degree_angle * M_PI / 180.0f;
    angle_radians *= time;

    mat4 matrix = init_Base(0);

    matrix.data[0][0] = 1;

    matrix.data[1][1] = cos(angle_radians);
    matrix.data[1][2] = -sin(angle_radians);

    matrix.data[2][1] = sin(angle_radians);
    matrix.data[2][2] = cos(angle_radians);

    matrix.data[3][3] = 1;

    return matrix;
}

mat4	look_At(vec3 eye, vec3 center, vec3 up) {
	vec3 cal;
	cal.x = center.x - eye.x;
	cal.y = center.y - eye.y;
	cal.z = center.z - eye.z;

	vec3 f = normalize(cal);
    vec3 r = normalize(cross(f, up));
    vec3 u = cross(r, f);

	mat4	matrix = init_Base(0);

    matrix.data[0][0] = r.x;
    matrix.data[1][0] = u.x;
    matrix.data[2][0] = -f.x;

    matrix.data[0][1] = r.y;
    matrix.data[1][1] = u.y;
    matrix.data[2][1] = -f.y;

    matrix.data[0][2] = r.z;
    matrix.data[1][2] = u.z;
    matrix.data[2][2] = -f.z;

    matrix.data[0][3] = -dot(r, eye);
    matrix.data[1][3] = -dot(u, eye);
    matrix.data[2][3] = dot(f, eye);
    matrix.data[3][3] = 1;

    return matrix;
}

vec3 cross(const vec3& a, const vec3& b) {
	vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
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

    float const rad = FOV * M_PI / 2.;
    float const tanHalfFovy = tan(rad / 2.);

    mat4    res = init_Base(0);

    res.data[0][0] = 1. / (aspect * tanHalfFovy);
    res.data[1][1] = 1. / (tanHalfFovy);
    res.data[2][2] = - (zFar + zNear) / (zFar - zNear);
    res.data[3][2] = - 1.;
    res.data[2][3] = - (2. * zFar * zNear) / (zFar - zNear);

    return (res);
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

mat4    mat_multiplication(mat4 a, mat4 b) {
    mat4    matrix;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            matrix.data[y][x] = a.data[y][0] * b.data[0][x] + a.data[y][1] * b.data[1][x] + a.data[y][2] * b.data[2][x] + a.data[y][3] * b.data[3][x];
        }
    }
    return matrix;
}

vec3    vec_multiplication(vec3 f, float s) {
    f.x = f.x * s;
    f.y = f.y * s;
    f.z = f.z * s;
    return (f);
}

vec3    vec_addition_egal(vec3 f, vec3 s) {
    f.x += s.x;
    f.y += s.y;
    f.z += s.z;
    return (f);
}

vec3    vec_substract_egal(vec3 f, vec3 s) {
    f.x -= s.x;
    f.y -= s.y;
    f.z -= s.z;
    return (f);
}