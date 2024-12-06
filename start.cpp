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
    RANDOM random;
public:
    bool RUN;
    bool TEST;
    Game(int width, int height, int row, int col, int ori):arena(Arena(width, height)), draw(Draw()),snake(Snake(row,col,ori)), random(RANDOM()), RUN(false), TEST(false) 
    {
        RUN = RUN_MODE;
        TEST = TEST_MODE;
    }

    //Ignore these tests
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

    void Data_test()
    {
        move(0,0);
        erase();
        mvprintw(1,1,"Random value: %i", random.RAND(1,10));
        refresh();
        napms(100);
    }

    void Game_Monitor()
    {
        mvprintw(5,5,"Length: %i", snake.size());
    }

    void Food_Update()
    {
        int row;
        int col;
        do
        {
            row = random.ROW(1,-1);
            col = random.COL(1,-1);
        } while (arena.mat(row, col) != 0);
        
        arena.insertFood(row, col);
        
    }

    //Set up value for test
    void Game_Setup(int len, int num)
    {
        //Initial length
        snake.increase(len);

        //Initial number of food
        for(int i = 0; i != num; ++i)
        {
            Food_Update();
        }
    }

    //Initialize the terminal environment
    void Game_start()
    {
        draw.start();
        draw.start_monitor();
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

    void Snake_update()
    {
        bool pop = snake.update();

        if(arena.mat(snake.head().row, snake.head().col) == 1)
        {
            arena.mat(snake.head().row, snake.head().col) = 0;
            snake.increase(1);
            Food_Update();
        }

        for(SnakeNode node:snake.body)
        {
            arena.mat(node.row, node.col) = -1;
        }

        if(pop)
        {
            arena.mat(snake.body.back().row, snake.body.back().col) = 0;
            snake.body.pop_back();
        }else
        {
            snake.INCREASE -= 1;
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

        Snake_update();
    }

    //Display everything(View)
    void Game_display()
    {
        draw.Draw_Arena(arena);
        draw.Draw_Snake(snake);
        draw.Draw_Monitor(snake);
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
    game.Game_Setup(SNAKE_START_LENGTH, FOOD_NUM);
    game.Game_start();
    while(game.RUN)
    {
        game.Game_listen();
        game.Game_update();
        game.Game_display();
    }
    while(game.TEST)
    {  
        game.Data_test();
    }
    game.Game_end();
    return 0;
}