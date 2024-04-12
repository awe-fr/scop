#pragma once

#include "./major.hpp"

class winApp;

mat4	ubo_init(winApp app, vec3 center);
UniformBufferObject computeMatricesFromInputs(winApp app, vec3 center);