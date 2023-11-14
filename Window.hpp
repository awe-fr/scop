#pragma once

#include "header.h"

class Window {
	private:
		std::string _title;
		int _width = 800;
		int _height = 800;
		bool _closed = false;
		SDL_Window *_window = nullptr;
		SDL_GLContext _context;
		bool init();
	public:
		Window(const std::string &title, int width, int height);
		~Window();
		bool isClosed() const;
		void	pollEvents();
};