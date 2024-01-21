#include "scopApp.hpp"

void    scopApp::run () {
    initWindow();
    initVulkan();
	mainLoop();
	cleanup();
}

void    scopApp::initWindow () {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->window = glfwCreateWindow(WIDTH, HEIGHT, "Scop", nullptr, nullptr);
}

void    scopApp::initVulkan () {

}

void    scopApp::mainLoop () {
    while (!glfwWindowShouldClose(this->window)) {
        glfwPollEvents();
    }
}

void    scopApp::cleanup () {
    glfwDestroyWindow(this->window);

    glfwTerminate();
}