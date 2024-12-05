#include "Arena.hpp"
#include "View.hpp"
#include "data.hpp"
#include <string>
#include <locale.h>
#include <windows.h>
#include <wchar.h>


void Draw::start()
{
    setlocale(LC_ALL, "");
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

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
    move(0,0);
    //clrtoeol();
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
}

void Draw::delay()
{
    refresh();
    napms(FRAMETIME);
}

void Draw::Draw_Snake(Snake s)
{
    for(SnakeNode node :s.body)
    {
        mvaddch(node.row, node.col, 's');
    }

    mvaddch(s.head().row, s.head().col, 'S');
}
