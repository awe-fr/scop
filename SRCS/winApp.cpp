#include "../headers/winApp.hpp"

void	winApp::init() {
    // glewExperimental = true;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit (1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(WIDTH, HEIGHT, "scop", NULL, NULL);
    if (this->window == NULL) {
        std::cerr << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        exit (1);
    }
    glfwMakeContextCurrent(this->window);
    // glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLUW" << std::endl;
        exit (1);
    }

    glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE); // keep key pushed
}

int		winApp::is_close() {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(this->window) != 0) {
        return 1;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(this->window);
    glfwPollEvents();

    return 0;
}

void    winApp::clear() {
    // glfwTerminate();
}