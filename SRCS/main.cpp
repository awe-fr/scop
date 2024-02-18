#include "../headers/major.h"

int	main(int ac, char **av) {
	winApp app;

	app.init();

	GLuint programID = LoadShaders( "./shaders/shader.vert", "./shaders/shader.frag" );
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);

	UniformBufferObject ubo;
	mat4	mvp;

	while(app.is_close() == 0) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, app.give_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

	ubo.proj = perspective(45, WIDTH / HEIGHT, 0.1f, 100.0f);


	vec3 eye; eye.x = 4; eye.y = 3; eye.z = 3;
	vec3 center; center.x = 0; center.y = 0; center.z = 0;
	vec3 up; up.x = 0; up.y = 1; up.z = 0;

	ubo.view = look_At(eye, center, up);

	ubo.model = init_Base(1);

	// mvp = mvp();









	}
	app.clear();
}