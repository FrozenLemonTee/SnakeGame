#include "iostream"
#include "data.hpp"
#include "arena.hpp"
#include "curses.h"
#include "View.hpp"


//Controller
class Game{
private:
    Arena arena;
    Draw draw;
    Snake snake;
public:
    bool RUN;
    Game(int width, int height, int row, int col, int ori):arena(Arena(width, height)), draw(Draw()),snake(Snake(row,col,ori)), RUN(true) {}

    //Game_monitor() and Key_test() are only for test
    void Game_monitor()
    {
        move(0,0);
        clrtoeol();
        printw("Orientation: %i \n", snake.orientation);
    }

    void Key_test()
    {
        int ch;

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
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


    //Set up value for test
    void Game_Setup(int len)
    {
        snake.increase(len);
        arena.insertFood(20,20);
        arena.insertFood(24,27);
        arena.insertFood(29,25);
        arena.insertFood(24,29);
        arena.insertFood(27,25);
    }

    //Initialize the terminal environment
    void Game_start()
    {
        draw.start();
    }

    //listen to keyboard input
    void Game_listen()
    {
        char ch = getch();

        if(ch == 'q')
        {
            RUN = false;
        }else
        {
            snake.listen(ch);
        }
    }

    //Update the interaction between Snake and other objects
    void Interaction_update()
    {
        //Update food
        if(arena.mat(snake.head().row, snake.head().col) == 1)
        {
            arena.mat(snake.head().row, snake.head().col) = 0;
            snake.increase(1);
        }
    }

    //Compose evert update together and check wheter Game is ended
    void Game_update()
    {
        if(snake.border())
        {
            RUN = false;
            return;
        }

        Interaction_update();
        snake.update();
    }

    //Display everything(View)
    void Game_display()
    {
        draw.Draw_Arena(arena);
        draw.Draw_Snake(snake);
        draw.delay();
    }

    void Game_end()
    {
        draw.end();
    }
};


int main()
{
    Game game = Game(WIDTH, HEIGHT, SNAKE_START_ROW, SNAKE_START_COL, SNAKE_START_ORI);
    game.Game_Setup(SNAKE_START_LENGTH);
    game.Game_start();
    while(game.RUN)
    {
        game.Game_listen();
        game.Game_update();
        game.Game_display();
    }
    game.Game_end();
}