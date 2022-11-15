//
// Created by sheep on 11/14/22.
//

#include "window.h"
#include <stdio.h>

window::window(int width, int height) {
    this->width = width;
    this->height = height;
}

bool window::initialize() {
    this->glfwWindow = glfwCreateWindow(500, 500, "My Window", nullptr, nullptr);
    if (this->glfwWindow == nullptr) {
        fprintf(stderr, "Failed to create a GLFW window.\n");
        glfwTerminate();
        return false;
    }

    return true;
}

void window::makeContextCurrent() {
    glfwMakeContextCurrent(this->glfwWindow);
}

bool window::shouldClose() {
    return glfwWindowShouldClose(this->glfwWindow);
}

void window::swapBuffers() {
    glfwSwapBuffers(this->glfwWindow);
}
