#include "../headers/major.hpp"

extern float   deltaTime;
extern float   transValue;

void	variation(bool updown) {
	float	value = 0.01;
	if (updown == true && transValue < 1)
		transValue += value;
	else if (updown == false && transValue > 0)
		transValue -= value;
}

mat4	ubo_init(winApp app, vec3 mid) {
	UniformBufferObject ubo;
	mat4	mvp;

	ubo = computeMatricesFromInputs(app, mid);

	mvp = mat_multiplication(ubo.proj, mat_multiplication(ubo.view, ubo.model));

	return (mvp);
}

UniformBufferObject	computeMatricesFromInputs(winApp app, vec3 mid) {
	static UniformBufferObject ubo;

	//translation
	static mat4 trans = init_Base(1);
	trans.data[0][3] = -mid.x;
	trans.data[1][3] = -mid.y;
	trans.data[2][3] = -mid.z;

	//timer
	static auto startTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	//transition bool
	static bool transitionCursor = false;
	static bool	pushed = false;

	//initial position
	static vec3 position = {0, 0, 0};

	//where and how look
	static float horizontalAngle = 0.0f;
	static float verticalAngle = 0.0f;
	static float FoV = 45.0f;

	//speed
	float speed = 3.0f;

	//vector for where we look
	vec3 direction; direction.x = cos(verticalAngle) * sin(horizontalAngle); direction.y = sin(verticalAngle); direction.z = cos(verticalAngle) * cos(horizontalAngle);
	vec3 right; right.x = sin(horizontalAngle - 3.14f/2.0f); right.y = 0; right.z = cos(horizontalAngle - 3.14f/2.0f);
	vec3 up = cross(right, direction);

	if (glfwGetKey(app.give_win(), GLFW_KEY_W) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(direction, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_S) == GLFW_PRESS)  {
		position = vec_substract_egal(position, vec_multiplication(direction, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_D) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(right, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_A) == GLFW_PRESS) {
		position = vec_substract_egal(position, vec_multiplication(right, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		position = vec_addition_egal(position, vec_multiplication(up, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position = vec_substract_egal(position, vec_multiplication(up, deltaTime * speed));
	}
	if (glfwGetKey(app.give_win(), GLFW_KEY_T) == GLFW_PRESS) {
		if (pushed == false){
			transitionCursor = !transitionCursor;
			pushed = true;
		}
	}
	else 
		pushed = false;
	variation(transitionCursor);

	ubo.proj = perspective(FoV, (double)WIDTH / (double)HEIGHT, 0.1f, 100.0f);
	ubo.view = look_At(position, vec_addition_egal(position, direction), up);
	ubo.model = rotate_y(time, 90);
	ubo.model = mat_multiplication(ubo.model,trans);

	return (ubo);
}