//
// Created by sheep on 11/14/22.
//

#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "window.h"

class engine {
public:
    engine(int width, int height);
    bool initialize();
    window* getWindow();
private:
    window* window;
};


#endif //ENGINE_ENGINE_H
