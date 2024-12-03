#ifndef ARENA_H
#define ARENA_H

#include <vector>

class Arena{
private:
    int width;
    int height;
    std::vector<std::vector<int>> matrix;
public:
    Arena(int w, int h);

    int& mat(int row, int col);
};

#endif