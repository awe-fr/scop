#pragma once

#include "./major.hpp"

class winApp;

mat4	ubo_init(winApp app);
UniformBufferObject computeMatricesFromInputs(winApp app);