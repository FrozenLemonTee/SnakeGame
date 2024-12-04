#include <vector>
#include "Arena.hpp"
#include "curses.h"


Arena::Arena(int w, int h): width(w), height(h), matrix(h, std::vector<int>(w,0)) {}

int& Arena::mat(int row, int col)
{
    return matrix[row][col];
}


SnakeNode::SnakeNode(int row, int col): row{row}, col{col} {}

void SnakeNode::copyNode(SnakeNode next)
{
    row = next.row;
    col = next.col;
}

SnakeNode SnakeNode::moveUp()
{
    return SnakeNode(row+1, col);
}

SnakeNode SnakeNode::moveDown()
{
    return SnakeNode(row-1, col);
}

SnakeNode SnakeNode::moveLeft()
{
    return SnakeNode(row, col-1);
}

SnakeNode SnakeNode::moveRight()
{
    return SnakeNode(row, col+1);
}



Snake::Snake(int row, int col, int ori): orientation{ori}
{
    body.push_front(SnakeNode(row, col));
}

SnakeNode Snake::head()
{
    return body.front();
}

int Snake::size()
{
    return body.size();
}

void Snake::update()
{
    switch(orientation)
    {
        case 1:
            body.push_front(head().moveUp());
        case 2:
            body.push_front(head().moveRight());
        case 3:
            body.push_front(head().moveDown());
        case 4:
            body.push_front(head().moveLeft());
        default:
            return;
    }
    body.pop_back();
}

void Snake::listen()
{
    char ch = getchar();
    switch(ch)
    {
        case 'w':
            orientation = 1;
        case 'd':
            orientation = 2;
        case 's':
            orientation = 3;
        case 'a':
            orientation = 4;
    }

}