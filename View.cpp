#include "Arena.hpp"
#include "View.hpp"
#include "data.hpp"
#include <string>

void Draw::start()
{
    initscr();
    curs_set(0);
}

void Draw::end()
{
    endwin();
}

void Draw::Draw_Arena(Arena a)
{
    erase();

    for (int row = 0; row != HEIGHT; ++row)
    {
        for (int col = 0; col != WIDTH; ++col)
        {
            printw("-");
        }

        printw("\n");
    }

    refresh();
    napms(FRAMETIME);
}