#include "../headers/major.hpp"

extern float   deltaTime;

mat4    nextProjMat;
mat4    nextViewMat;
mat4    nextModelMat;

#include <stdio.h>

void	print_mat(mat4 m)
{
	for (int i = 0; i < 4; ++i)
		printf("%3.3f %3.3f %3.3f %3.3f\n", m.data[i][0], m.data[i][1], m.data[i][2], m.data[i][3]);
}

mat4	ubo_init(winApp app) {
	UniformBufferObject ubo;
	mat4	mvp;

	ubo = computeMatricesFromInputs(app);

	// static auto startTime = std::chrono::high_resolution_clock::now();
	// static float dx = 0;
	// static float dy = 0;
	// static float dz = 0;

    // auto currentTime = std::chrono::high_resolution_clock::now();
    // float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	// if ((int)time % 15 >= 10)
	// 	ubo.model = rotate_y(time, 90);
	// else if ((int)time % 15 >= 5)
	// 	ubo.model = rotate_x(time, 90);
	// else
	// 	ubo.model = rotate_z(time, 90);

	// ubo.model = rotate_y(time, 90);
    
	// ubo.proj = perspective(45, 4 / 3, 0.1f, 100.0f);

	// vec3 eye; eye.x = 0; eye.y = 0; eye.z = 5;
	// vec3 center; center.x = 0; center.y = 0; center.z = 0;
	// vec3 up; up.x = 0; up.y = 1; up.z = 0;
	// ubo.view = look_At(eye, center, up);

	// ubo.proj = getProjectionMatrix();

	// ubo.view = getViewMatrix();

	// ubo.model = getModelMatrix();

	// printf("--- MODEL ---\n");
	// print_mat(ubo.model);
	// printf("--- VIEW ---\n");
	// print_mat(ubo.view);
	// printf("--- PROJ ---\n");
	// print_mat(ubo.proj);

	mvp = mat_multiplication(ubo.proj, mat_multiplication(ubo.view, ubo.model));

	return (mvp);
}

UniformBufferObject	computeMatricesFromInputs(winApp app) {
	UniformBufferObject ubo;

	//initial position
	static vec3 position = {0, 0, 0};

	//where and how look
	static float horizontalAngle = 3.14f;
	static float verticalAngle = 0.0f;
	static float initialFoV = 45.0f;

	//speed
	float speed = 3.0f;
	float mouseSpeed = 0.005f;

	//get mouse pos
	double xpos, ypos;
	glfwGetCursorPos(app.give_win(), &xpos, &ypos);

	//restart mouse pos
	glfwSetCursorPos(app.give_win(), WIDTH/2, HEIGHT/2);

	//cal new orientation
	horizontalAngle += mouseSpeed * deltaTime * float((float)WIDTH/2. - xpos);
	verticalAngle   += mouseSpeed * deltaTime * float((float)HEIGHT/2. - ypos);

	//vector for where we look
	vec3 direction; direction.x = cos(verticalAngle) * sin(horizontalAngle); direction.y = sin(verticalAngle); direction.z = cos(verticalAngle) * cos(horizontalAngle);
	vec3 right; right.x = sin(horizontalAngle - 3.14f/2.0f); right.y = 0; right.z = cos(horizontalAngle - 3.14f/2.0f);
	vec3 up = cross(right, direction);

	if (glfwGetKey(app.give_win(), GLFW_KEY_UP) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(direction, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_DOWN) == GLFW_PRESS)  {
		position = vec_substract_egal(position, vec_multiplication(direction, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(right, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		position = vec_substract_egal(position, vec_multiplication(right, deltaTime * speed));
	}

	float FoV = initialFoV;

	ubo.proj = perspective(FoV, (double)WIDTH / (double)HEIGHT, 0.1f, 100.0f);

	ubo.view = look_At(position, vec_addition_egal(position, direction), up);

	ubo.model = init_Base(1);

	return (ubo);
}

mat4	getProjectionMatrix() {
	return (nextProjMat);
}

mat4	getViewMatrix() {
	return (nextViewMat);
}

mat4	getModelMatrix() {
	return (nextModelMat);
}