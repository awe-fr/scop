#pragma once

#include "header.h"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class	scopApp {
	public:
		void	run();
	private:
        GLFWwindow  *window;
        void    initWindow();
		void	initVulkan();
		void	mainLoop();
		void	cleanup ();
};