#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "./winApp.hpp"

const int WIDTH = 800;
const int HEIGHT = 600;

GLuint  LoadShaders(const char * vertex_file_path,const char * fragment_file_path);