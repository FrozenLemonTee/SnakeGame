#ifndef DATA_H
#define DATA_H

#include <random>

class RANDOM{
    std::random_device rd;
    std::mt19937 gen;
public:
    RANDOM();
    int RAND(int min, int max);
    int ROW(int roffset, int coffset);
    int COL(int roffset, int coffset);

};

extern const int WIDTH;
extern const int HEIGHT;
extern const int M_WIDTH;
extern const int M_HEIGHT;
extern const int FRAMETIME;

extern const int SNAKE_START_ROW;
extern const int SNAKE_START_COL;
extern const int SNAKE_START_ORI;
extern const int SNAKE_START_LENGTH;

extern const int FOOD_NUM;
extern const int OBS_NUM;


extern const bool TEST_MODE;
extern const bool RUN_MODE;
extern const bool ALL_DIR_MODE;



#endif