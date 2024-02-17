#pragma once

#include "./major.h"

static const GLfloat g_vertex_buffer_data[] = {
   -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f,
};

class	winApp {
	private:
		GLFWwindow*	window;
		GLuint		VertexArrayID;
		GLuint		vertexbuffer;
	public:
		void	init();
		int		is_close();
		void	clear();
		void	create_VAO();
		void	create_vertex_buffer();
		GLuint	give_vertex_buffer();
};