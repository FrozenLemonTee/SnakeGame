#include <vector>
#include "Arena.hpp"


Arena::Arena(int w, int h): width(w), height(h), matrix(h, std::vector<int>(w,0)) {}

int& Arena::mat(int row, int col)
{
    return matrix[row][col];
}