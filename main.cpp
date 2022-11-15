#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "engine.h"

int main() {
    engine e(720, 720);
    if (!e.initialize()) {
        fprintf(stderr, "Failed to initialize engine.\n");
    }

    // create shaders
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vShaderSource;
    std::ifstream vShaderStream("../vertex.glsl", std::ios::in);
    if (vShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << vShaderStream.rdbuf();
        vShaderSource = sstr.str();
        vShaderStream.close();
    } else {
        fprintf(stderr, "Failed to open vertex shader source file.\n");
    }

    const char* c_vShaderSource = vShaderSource.c_str();
    glShaderSource(vShader, 1, &c_vShaderSource, nullptr);
    glCompileShader(vShader);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> error(InfoLogLength+1);
        glGetShaderInfoLog(vShader, InfoLogLength, NULL, &error[0]);
        printf("%s\n", &error[0]);
    } else {
        printf("Successfully compiled vertex shader.\n");
    }

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fShaderSource;
    std::ifstream fShaderStream("../fragment.glsl", std::ios::in);
    if (fShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << fShaderStream.rdbuf();
        fShaderSource = sstr.str();
        fShaderStream.close();
    } else {
        fprintf(stderr, "Failed to open fragment shader source file.\n");
    }

    const char* c_fShaderSource = fShaderSource.c_str();
    glShaderSource(fShader, 1, &c_fShaderSource, nullptr);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> error(InfoLogLength+1);
        glGetShaderInfoLog(fShader, InfoLogLength, NULL, &error[0]);
        printf("%s\n", &error[0]);
    } else {
        printf("Successfully compiled fragment shader.\n");
    }

    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vShader);
    glAttachShader(ProgramID, fShader);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, vShader);
    glDetachShader(ProgramID, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

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

        glUseProgram(ProgramID);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        e.getWindow()->swapBuffers();
        glfwPollEvents();
    }
}