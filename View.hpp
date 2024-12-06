#ifndef VIEW_H
#define VIEW_H

#include "curses.h"
#include "Arena.hpp"

class Draw{
private:
    WINDOW *monitor;
public:
    void start();
    void start_monitor();
    void delay();
    void end();
    void Draw_Arena(Arena a);
    void Draw_Snake(Snake s);
    void Draw_Monitor(Snake s);
};




#endif