#include "../headers/major.hpp"

extern float   deltaTime;

mat4    nextProjMat;
mat4    nextViewMat;
mat4    nextModelMat;


mat4	ubo_init(winApp app) {
	UniformBufferObject ubo;
	mat4	mvp;

	// static auto startTime = std::chrono::high_resolution_clock::now();

    // auto currentTime = std::chrono::high_resolution_clock::now();
    // float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	// if ((int)time % 15 >= 10)
	// 	ubo.model = rotate_y(time, 90);
	// else if ((int)time % 15 >= 5)
	// 	ubo.model = rotate_x(time, 90);
	// else
	// 	ubo.model = rotate_z(time, 90);
    
	// ubo.proj = perspective(45, 4 / 3, 0.1f, 100.0f);

	// vec3 eye; eye.x = 4; eye.y = 3; eye.z = 3;
	// vec3 center; center.x = 0; center.y = 0; center.z = 0;
	// vec3 up; up.x = 0; up.y = 1; up.z = 0;
	// ubo.view = look_At(eye, center, up);

	// ubo.model = init_Base(1);

	ubo = computeMatricesFromInputs(app);

	// ubo.proj = getProjectionMatrix();

	// ubo.view = getViewMatrix();

	// ubo.model = getModelMatrix();

	mvp = mat_multiplication(mat_multiplication(ubo.proj, ubo.view), ubo.model);

	return (mvp);
}

UniformBufferObject	computeMatricesFromInputs(winApp app) {
	UniformBufferObject ubo;

	//initial position
	vec3 position; position.x = 0; position.y = 0; position.z = 5;

	//where and how look
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;

	//speed
	float speed = 3.0f;
	float mouseSpeed = 0.005f;

	//get mouse pos
	double xpos, ypos;
	glfwGetCursorPos(app.give_win(), &xpos, &ypos);

	//restart mouse pos
	glfwSetCursorPos(app.give_win(), WIDTH/2, HEIGHT/2);

	//cal new orientation
	horizontalAngle += mouseSpeed * deltaTime * float(WIDTH/2 - xpos);
	verticalAngle   += mouseSpeed * deltaTime * float(HEIGHT/2 - ypos);

	//vector for where we look
	vec3 direction; direction.x = cos(verticalAngle) * sin(horizontalAngle); direction.y = sin(verticalAngle); direction.z = cos(verticalAngle) * cos(horizontalAngle);
	vec3 right; right.x = sin(horizontalAngle - 3.14f/2.0f); right.y = 0; right.z = cos(horizontalAngle - 3.14f/2.0f);
	vec3 up = cross(right, direction);

	if (glfwGetKey(app.give_win(), GLFW_KEY_UP) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(vec_multiplication(direction, deltaTime), speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		position = vec_substract_egal(position, vec_multiplication(vec_multiplication(direction, deltaTime), speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		position = vec_addition_egal(right, vec_multiplication(vec_multiplication(direction, deltaTime), speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		position = vec_substract_egal(right, vec_multiplication(vec_multiplication(direction, deltaTime), speed));
	}

	float FoV = initialFoV;

	ubo.proj = perspective(FoV, WIDTH / HEIGHT, 0.1f, 100.0f);

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