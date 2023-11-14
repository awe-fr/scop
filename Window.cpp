#include "Window.hpp"

Window::Window(const std::string &title, int width, int height)
{
	this->_title = title;
	this->_width = width;
	this->_height = height;
	if (init() == false)
		this->_closed = true; 
}

Window::~Window()
{
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
}

bool Window::isClosed() const
{
	return (this->_closed);
}

bool Window::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0)
	{
		std::cerr << "Failed to initialize SDL." << std::endl;
		return 0;
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	this->_window = SDL_CreateWindow(this->_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->_width, this->_height, 0);
	if (this->_window == nullptr) 
	{
		std::cerr << "Failed to create window." << std::endl;
		return 0;
	}
	this->_context = SDL_GL_CreateContext(this->_window);
	return true;
}

void	Window::pollEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				this->_closed = true;
				break;
			default:
				break;
		}
	}
}