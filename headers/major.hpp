#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <cstring>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>

#include "./subMath.hpp"
#include "./winApp.hpp"
#include "./controls.hpp"

#define FOURCC_DXT1 0x31545844
#define FOURCC_DXT3 0x33545844
#define FOURCC_DXT5 0x35545844

const int WIDTH = 800;
const int HEIGHT = 600;

void	getDeltaTime();

GLuint	LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

bool	loadOBJ(const char* path, std::vector<vec3>& out_vertices);

GLuint	loadDDS(const char *imagepath);
GLuint 	loadBMP_custom(const char * imagepath);
GLuint 	loadTGA(const char *imagepath);