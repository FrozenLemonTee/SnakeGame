#include "iostream"
#include "data.hpp"
#include "arena.hpp"
#include "curses.h"
#include "View.hpp"


//Controller
class Game{
    Arena arena;
    Draw draw;
    Snake snake;
    RANDOM random;
public:
    bool RUN;
    bool TEST;
    Game(const int width, const int height,
         const int row, const int col, const int ori)
       : arena(Arena(width, height)), draw(Draw()),
         snake(Snake(row,col,ori)), RUN(false), TEST(false)
    {
        RUN = RUN_MODE;
        TEST = TEST_MODE;
    }

    //Ignore these tests
    [[noreturn]] static void Key_test()
    {
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        curs_set(0);

        while(true)
        {
            //flushinp();
            const int ch = getch();
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
        int row = 0;
        int col = 0;
        do
        {
            row = random.ROW(1,-1);
            col = random.COL(1,-1);
        } while (arena.mat(row, col) != 0);
        
        arena.insertFood(row, col);
        
    }

    void Obs_Update()
    {
        int row = 0;
        int col = 0;
        do
        {
            row = random.ROW(5, -5);
            col = random.COL(15,-15);
        } while (arena.mat(row,col) != 0
                || arena.mat(row+1,col) != 0
                || arena.mat(row,col+1) != 0
                || arena.mat(row+1,col+1) != 0);

        arena.insertObs(row,col);
        arena.insertObs(row+1,col);
        arena.insertObs(row,col+1);
        arena.insertObs(row+1,col+1);
        
    }

    //Set up value for test
    void Game_Setup(const int len, const int Food_num, const int Obs_num)
    {
        //Initial length
        snake.increase(len);

        //Initial number of food
        for(int i = 0; i != Food_num; ++i)
        {
            Food_Update();
        }

        for(int i = 0; i != Obs_num; ++i)
        {
            Obs_Update();
        }
    }

    //Initialize the terminal environment
    void Game_start()
    {
        draw.start();
        draw.start_monitor();
    }

    //listen to keyboard input
    void Game_listen(const bool bl)
    {
        const char ch = getch();

        if(ch == 'q')
        {
            RUN = false;
            return;
        }
    
        if(bl)
        {
            snake.listen_All_Dir(ch);
        }else
        {
            snake.listen(ch);
        }
    
    }
    

    void Snake_update()
    {
        //push front the new head
        const bool pop = snake.update();

        //manage interaction
        if(arena.mat(snake.head().row, snake.head().col) == 1)
        {
            arena.mat(snake.head().row, snake.head().col) = 0;
            snake.increase(1);
            Food_Update();
        }else if((arena.mat(snake.head().row, snake.head().col) == -2))
        {
            RUN = false;
            return;
        }else if((arena.mat(snake.head().row, snake.head().col) == -1))
        {
            //check whether it is other's body
            bool selfBody = false;
            for(const SnakeNode node: snake.body)
            {
                if(snake.head().row == node.row
                && snake.head().col == node.col)
                {
                    selfBody = true;
                }
            }
            if(selfBody == false)
            {
                RUN = false;
                return;
            }
            RUN = true;
        } 

        //update body on chess
        for(const SnakeNode node:snake.body)
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


    //Compose evert update together and check whether Game is ended
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
    Game game(WIDTH, HEIGHT, SNAKE_START_ROW, SNAKE_START_COL, SNAKE_START_ORI);
    game.Game_Setup(SNAKE_START_LENGTH, FOOD_NUM, OBS_NUM);
    game.Game_start();
    while(game.RUN)
    {
        game.Game_listen(ALL_DIR_MODE);
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