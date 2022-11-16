#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"

int main() {
    engine e(720, 720);
    if (!e.initialize()) {
        fprintf(stderr, "Failed to initialize engine.\n");
    }

    // create shaders
    shader shader1("../vertex.glsl", "../fragment.glsl");
    e.setShader(&shader1);

    // create vao
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // verts
    static const GLfloat vertices[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    // create vbo
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    while (!e.getWindow()->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        e.getWindow()->swapBuffers();
        glfwPollEvents();
    }
}