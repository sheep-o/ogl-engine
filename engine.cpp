//
// Created by sheep on 11/14/22.
//

#include <GL/glew.h>
#include "engine.h"
#include <stdio.h>

engine::engine(int width, int height) {
    this->window = new class window(width, height);
}

bool engine::initialize() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    this->window->initialize();
    this->window->makeContextCurrent();

    //glfwMakeContextCurrent(this->window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW.\n");
        //glfwDestroyWindow(this->window);
        glfwTerminate();
        return false;
    }

    return true;
}

window* engine::getWindow() {
    return this->window;
}
