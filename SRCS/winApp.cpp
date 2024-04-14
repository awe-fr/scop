#include "../headers/winApp.hpp"

void	winApp::init(std::vector<vec3> vertices) {
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
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLUW" << std::endl;
		exit (1);
	}

	glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE); // keep key pushed

	this->init_color_buffer(vertices);
	this->create_VAO();
	this->create_texture_buffer(vertices);
	this->create_vertex_buffer(vertices);
}

int		winApp::is_close() {
	if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->window) != 0)
		return 1;

	// glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(this->window);
	glfwPollEvents();

	return 0;
}

void    winApp::clear() {
	glfwTerminate();
}

void	winApp::create_VAO() {
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
}

void	winApp::init_color_buffer(std::vector<vec3> vertices) {
	GLfloat g_color_buffer_data[vertices.size() * 4];
	int i = 0;
	while (i < vertices.size() * 4) {
		if (i  % 36 < 12) {
			g_color_buffer_data[i] = 0.1f;
			g_color_buffer_data[i + 1] = 0.1f;
			g_color_buffer_data[i + 2] = 0.1f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		else if (i % 36 < 24){
			g_color_buffer_data[i] = 0.2f;
			g_color_buffer_data[i + 1] = 0.2f;
			g_color_buffer_data[i + 2] = 0.2f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		else {
			g_color_buffer_data[i] = 0.3f;
			g_color_buffer_data[i + 1] = 0.3f;
			g_color_buffer_data[i + 2] = 0.3f;
			g_color_buffer_data[i + 3] = 1.0f;
		}
		i += 4;
	}
	glGenBuffers(1, &this->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void	winApp::create_vertex_buffer(std::vector<vec3> vertices) {
	glGenBuffers(1, &this->vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
}

void	winApp::create_texture_buffer(std::vector<vec3> vertices) {
	GLuint	image = loadDDS("./textures/test.dds");
	GLfloat g_uv_buffer_data[vertices.size() * 2];
	int i = 0;
	int j = 0;
	while (i < vertices.size() * 2) {
		g_uv_buffer_data[i] = vertices[j].z * 2;
		g_uv_buffer_data[i + 1] = vertices[j].y * 2;
		j++;
		i += 2;
	}
	glGenBuffers(1, &this->texturebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->texturebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

GLuint	winApp::give_color_buffer() {
	return (this->colorbuffer);
}

GLuint	winApp::give_vertex_buffer() {
	return (this->vertexbuffer);
}

GLuint	winApp::give_texture_buffer() {
	return (this->texturebuffer);
}

GLFWwindow	*winApp::give_win() {
	return (this->window);
}
