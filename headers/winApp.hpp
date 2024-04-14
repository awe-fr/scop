#pragma once

#include "./major.hpp"

class	winApp {
	private:
		GLFWwindow*	window;
		GLuint		VertexArrayID;
		GLuint		vertexbuffer;
		GLuint		colorbuffer;
        GLuint      texturebuffer;
        GLfloat     *g_color_buffer_data;
	public:
		void	init(std::vector<vec3> vertices);
		int		is_close();
		void	clear();
		void	create_VAO();
        void    init_color_buffer(std::vector<vec3> vertices);
		void	create_vertex_buffer(std::vector<vec3> vertices);
        void	create_texture_buffer(std::vector<vec3> vertices);
		GLuint	give_vertex_buffer();
		GLuint	give_color_buffer();
        GLuint	give_texture_buffer();
        GLFWwindow	*give_win();
};