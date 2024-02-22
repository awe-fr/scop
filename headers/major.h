#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>

#include "./winApp.hpp"
#include "./subMath.h"

const int WIDTH = 800;
const int HEIGHT = 600;

GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

GLuint  loadBMP_custom(const char * imagepath);
GLuint  loadTGA_glfw(const char *imagepath);
GLuint  loadTGA(const char *imagepath);