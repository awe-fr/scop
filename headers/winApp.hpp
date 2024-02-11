#pragma once

#include "./major.h"

class	winApp {
	private:
		GLFWwindow*	window;
	public:
		void	init();
		int		is_close();
		void	clear();
};