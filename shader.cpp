//
// Created by sheep on 11/15/22.
//

#include "shader.h"
#include <fstream>
#include <sstream>
#include <vector>

shader::shader(const char *vPath, const char *fPath) {
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

    this->program = glCreateProgram();
    glAttachShader(this->program, vShader);
    glAttachShader(this->program, fShader);
    glLinkProgram(this->program);

    // Check the program
    glGetProgramiv(this->program, GL_LINK_STATUS, &Result);
    glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(this->program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(this->program, vShader);
    glDetachShader(this->program, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

GLuint shader::getProgram() {
    return this->program;
}
