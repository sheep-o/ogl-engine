//
// Created by sheep on 11/14/22.
//

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include <GLFW/glfw3.h>

class window {
public:
    window(int width, int height);
    bool initialize();
    bool shouldClose();
    void makeContextCurrent();
    void swapBuffers();

private:
    int width;
    int height;
    GLFWwindow* glfwWindow;
};


#endif //ENGINE_WINDOW_H
