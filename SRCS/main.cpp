#include "../headers/major.hpp"

float   deltaTime;

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

int	main(int ac, char **av) {
	winApp app;

	app.init();

	GLuint	image = loadDDS("./textures/test4.dds");

	GLuint programID = LoadShaders( "./shaders/shader.vert", "./shaders/shader.frag" );
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	// glDepthFunc(GL_LESS);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);

	while(app.is_close() == 0) {
		getDeltaTime();

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

		mat4	mvp = ubo_init(app);
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		float	buf[16] = {0};
		populate(buf, mvp);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, buf);
	}
	app.clear();
}

float getDeltaTime() {
	static double last = glfwGetTime();

	double now = glfwGetTime();
	deltaTime = (float)(now - last);
	last = now;
}