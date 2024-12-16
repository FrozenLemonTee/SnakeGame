#ifndef VIEW_H
#define VIEW_H

#include "curses.h"
#include "Arena.hpp"

class Draw{
    WINDOW *monitor;
public:
    static void start();
    void start_monitor();
    void delay() const;
    void end() const;
    static void Draw_Arena(Arena a);
    static void Draw_Snake(const Snake& s);
    void Draw_Monitor(const Snake& s) const;
};




#endif