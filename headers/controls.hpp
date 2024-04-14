#pragma once

#include "./major.hpp"

class winApp;

/* inputs and matrix calculation */

mat4				ubo_init(winApp app);
UniformBufferObject	computeMatricesFromInputs(winApp app);