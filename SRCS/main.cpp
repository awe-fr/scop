#include "../headers/major.h"

mat4	ubo_init(void);

int	main(int ac, char **av) {
	winApp app;

	app.init();

	GLuint	image = loadTGA("./textures/uvtemplate.tga");

	GLuint programID = LoadShaders( "./shaders/shader.vert", "./shaders/shader.frag" );
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

	while(app.is_close() == 0) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, app.give_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, app.give_texture_buffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// glEnableVertexAttribArray(1);
		// glBindBuffer(GL_ARRAY_BUFFER, app.give_color_buffer());
		// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		mat4	mvp = ubo_init();

		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp.data[0][0]);


	}
	app.clear();
}

mat4	ubo_init(void) {
	UniformBufferObject ubo;
	mat4	mvp;

	static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	if ((int)time % 15 >= 10)
		ubo.model = rotate_y(time, 90);
	else if ((int)time % 15 >= 5)
		ubo.model = rotate_x(time, 90);
	else
		ubo.model = rotate_z(time, 90);

	ubo.proj = perspective(45, 4 / 3, 0.1f, 100.0f);

	vec3 eye; eye.x = 4; eye.y = 3; eye.z = 3;
	vec3 center; center.x = 0; center.y = 0; center.z = 0;
	vec3 up; up.x = 0; up.y = 1; up.z = 0;

	ubo.view = look_At(eye, center, up);
	// ubo.model = init_Base(1);

	mvp = mat_multiplication(mat_multiplication(ubo.proj, ubo.view), ubo.model);

	return (mvp);
}