#pragma once

#include "./major.hpp"

class winApp;

/* inputs and matrix calculation */

void				variation(bool updown);
mat4				ubo_init(winApp app, vec3 mid);
UniformBufferObject	computeMatricesFromInputs(winApp app, vec3 mid);