#include "iostream"
#include "data.hpp"
#include "arena.hpp"
#include "curses.h"
#include "View.hpp"

void test()
{
    Arena arena = Arena(WIDTH, HEIGHT);
    Draw draw = Draw();
    Snake snake = Snake(10,10,2);

    snake.body.push_back(SnakeNode(10,11));
    snake.body.push_back(SnakeNode(10,12));
    snake.body.push_back(SnakeNode(10,13));
    snake.body.push_back(SnakeNode(10,14));

    draw.start();
    while(true)
    {
        char ch = getch();
        snake.listen(ch);
        snake.update();
        draw.Draw_Arena(arena);
        draw.Draw_Snake(snake);
        draw.delay();
    }
    draw.end();
}

void test_input()
{
    int ch;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(0);

    while(true)
    {
        //flushinp();
        ch = getch();
        if(ch != -1)
        {
            move(0,0);
            clrtoeol();
            printw("Captured Key: %c \n", ch);
        }

        refresh();
        napms(30);
    }

}

void monitor(Snake snake)
{
    move(0,0);
    clrtoeol();
    printw("Orientation: %i \n", snake.orientation);
}


int main()
{
    test();
}
