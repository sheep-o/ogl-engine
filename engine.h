//
// Created by sheep on 11/14/22.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "window.h"
#include "shader.h"

class engine {
public:
    engine(int width, int height);
    bool initialize();
    window* getWindow();
    void setShader(shader* shader1);
private:
    window* window;
    shader* mainShader;
};


#endif //ENGINE_ENGINE_H
