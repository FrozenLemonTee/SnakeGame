#include <iostream>
#include "data.hpp"
#include "arena.hpp"
#include "curses.h"
#include "View.hpp"

int main()
{
    Arena arena = Arena(WIDTH, HEIGHT);
    Draw draw = Draw();

    draw.start();
    while(true)
    {
        draw.Draw_Arena(arena);
        draw.delay();
    }
    draw.end();
}