#include "../headers/winApp.hpp"

void	winApp::init() {
	// glewExperimental = true;
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit (1);
	}

	glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "scop", NULL, NULL);
	if (this->window == NULL) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit (1);
	}
	glfwMakeContextCurrent(this->window);
	// glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLUW" << std::endl;
		exit (1);
	}

	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE); // keep key pushed

	this->create_VAO();
	this->create_vertex_buffer();
	this->create_color_buffer();
}

int		winApp::is_close() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->window) != 0) {
		return 1;
	}

	// glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(this->window);
	glfwPollEvents();

	return 0;
}

void    winApp::clear() {
	// glfwTerminate();
}

void	winApp::create_VAO() {
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
}

void	winApp::create_color_buffer() {
	glGenBuffers(1, &this->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}


void	winApp::create_vertex_buffer() {
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

GLuint	winApp::give_color_buffer() {
	return (this->colorbuffer);
}

GLuint	winApp::give_vertex_buffer() {
	return (this->vertexbuffer);
}

