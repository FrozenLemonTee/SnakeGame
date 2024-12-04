#include "Arena.hpp"
#include "View.hpp"
#include "data.hpp"
#include <string>

void Draw::start()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

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
            if(a.mat(row,col) == 0)
            {
                printw("-");
            }
            else if (a.mat(row, col) == 1)
            {
                printw("#");
            }
        }

        printw("\n");
    }
}

void Draw::delay()
{
    refresh();
    napms(FRAMETIME);
}