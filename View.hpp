#ifndef VIEW_H
#define VIEW_H

#include "curses.h"
#include "Arena.hpp"

class Draw{

public:
    void start();
    void end();
    void Draw_Arena(Arena a);
};




#endif