#include <data.hpp>
#include <random>

RANDOM::RANDOM(): gen(rd()){}

int RANDOM::RAND(const int min, const int max)
{
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

int RANDOM::ROW(const int roffset, const int coffset)
{
    return RAND(0 + roffset, HEIGHT + coffset);
}

int RANDOM::COL(const int roffset, const int coffset)
{
    return RAND(0 + roffset, WIDTH + coffset);
}


int RANDOM(const int min, const int max)
{
    std::random_device RD;
    std::mt19937 gen(RD());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

const int WIDTH = 120;
const int HEIGHT = 30;
const int M_WIDTH = 30;
const int M_HEIGHT = 12;
const int FRAMETIME = 50; //ms

const int SNAKE_START_ROW = 10;
const int SNAKE_START_COL = 10;
const int SNAKE_START_ORI = 2;
const int SNAKE_START_LENGTH = 2;

const int FOOD_NUM = 20;
const int OBS_NUM = 20;

const bool TEST_MODE = false;
const bool RUN_MODE = true;
const bool ALL_DIR_MODE = false;