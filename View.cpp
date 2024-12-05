#include "Arena.hpp"
#include "View.hpp"
#include "data.hpp"
#include <string>
#include <locale.h>
#include <windows.h>
#include <wchar.h>


void Draw::start()
{
    //Configure UTF8 for windows terminal
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    initscr();
    cbreak(); //No buffer
    noecho(); //No echo
    curs_set(0); //No cursor
    keypad(stdscr, TRUE); //Use small keyboard
    nodelay(stdscr, TRUE); //Non block mode

}

void Draw::end()
{
    endwin();
}

void Draw::Draw_Arena(Arena a)
{
    erase();
    move(0,0); //move the cursor
    for(int col = 0; col != WIDTH + 1; ++col)
    {
        mvaddch(0,col,'-');
        mvaddch(HEIGHT,col,'-');
    }

    for(int row = 1; row != HEIGHT; ++row)
    {
        mvaddch(row,0,'[');
        mvaddch(row,WIDTH, ']');
    }

    for(int row = 1; row != HEIGHT; ++row)
    {
        for(int col = 1; col != WIDTH; ++col)
        {
            if(a.mat(row,col) == 1)
            {
                mvaddch(row, col, '$');
            }
        }
    }
}

void Draw::delay()
{
    refresh();
    napms(FRAMETIME);
}

void Draw::Draw_Snake(Snake s)
{
    //Draw body
    for(SnakeNode node :s.body)
    {
        mvaddch(node.row, node.col, 's');
    }

    //Draw the first piece of body, capitalising it because it is our head
    mvaddch(s.head().row, s.head().col, 'S');
}
