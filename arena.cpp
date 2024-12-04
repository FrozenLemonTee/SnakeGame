#include <vector>
#include "Arena.hpp"
#include "curses.h"
#include "data.hpp"


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
    return SnakeNode(row-1, col);
}

SnakeNode SnakeNode::moveDown()
{
    return SnakeNode(row+1, col);
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
    if(orientation == 1)
    {
        body.push_front(head().moveUp());
    }else if(orientation == 2)
    {
        body.push_front(head().moveRight());
    }else if(orientation == 3)
    {
        body.push_front(head().moveDown());
    }else if(orientation == 4)
    {
        body.push_front(head().moveLeft());
    }
    body.pop_back();
}

void Snake::listen(char ch)
{
    if(ch == 's')
    {
        orientation = 3;
    }else if(ch == 'w')
    {
        orientation = 1;
    }else if(ch == 'd')
    {
        orientation = 2;
    }else if(ch == 'a')
    {
        orientation = 4;
    }else
    {
        return;
    }

}

void Snake::increase()
{
}