//
// Created by sheep on 11/15/22.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include "GL/glew.h"

class shader {
public:
    shader(const char* vPath, const char* fPath);
    GLuint getProgram();
private:
    GLuint program;
};


#endif //ENGINE_SHADER_H
