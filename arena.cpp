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



Snake::Snake(int row, int col, int ori): orientation{ori}, INCREASE(0)
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

    if(INCREASE > 0)
    {
        INCREASE -= 1;
        return;
    }

    body.pop_back();
}

void Snake::listen(char ch)
{
    if(ch == 's' || ch == KEY_DOWN)
    {
        orientation = 3;
    }else if(ch == 'w' || ch == KEY_UP)
    {
        orientation = 1;
    }else if(ch == 'd' || ch == KEY_RIGHT)
    {
        orientation = 2;
    }else if(ch == 'a' || ch == KEY_LEFT)
    {
        orientation = 4;
    }else
    {
        return;
    }

}

void Snake::increase(int num)
{
    INCREASE += num;
}

bool Snake::border()
{
    if(head().row <= 0 && orientation == 1)
    {
        return true;
    }
    return false;
}