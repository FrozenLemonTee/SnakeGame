#include <vector>
#include "Arena.hpp"
#include "curses.h"
#include "data.hpp"


Arena::Arena(int w, int h): width(w), height(h), matrix(h, std::vector<int>(w,0)) {}

int& Arena::mat(int row, int col)
{
    return matrix[row][col];
}

void Arena::insertFood(int row, int col)
{
    if(matrix[row][col] == 0)
    {
        matrix[row][col] = 1;
    }else
    {
        return;
    }
}

void Arena::deleteFood(int row, int col)
{
    if(matrix[row][col] == 1)
    {
        matrix[row][col] = 0;
    }else
    {
        return;
    }
}

void Arena::insertObs(int row, int col)
{
    if(matrix[row][col] == 0)
    {
        matrix[row][col] = -2;
    }else
    {
        return;
    }
}


SnakeNode::SnakeNode(int row, int col): row{row}, col{col} {}

void SnakeNode::copyNode(SnakeNode next)
{
    //You can also define the operator= to implement this function
    row = next.row;
    col = next.col;
}


//These function returns a new node in different orientation
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

bool Snake::update()
{
    //Tips:
    //How do I move the Snake?
    //When snake moves, I add a new node at the front
    //And then remove the last node
    //If I want to increase the length of our node
    //I stop "remove the last node" for that single time

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
        //If I have INCREASE, I don't wanna pop back
        return false;
    }else
    {
        return true;
    }
}

void Snake::listen(char ch)
{
    //Don't know why KEY can not be detected, you better use wasd
    if((ch == 's' || ch == KEY_DOWN) && orientation != 1)
    {
        orientation = 3;
    }else if((ch == 'w' || ch == KEY_UP) && orientation != 3)
    {
        orientation = 1;
    }else if((ch == 'd' || ch == KEY_RIGHT) && orientation != 4)
    {
        orientation = 2;
    }else if((ch == 'a' || ch == KEY_LEFT) && orientation != 2)
    {
        orientation = 4;
    }else
    {
        return;
    }
}

void Snake::listen_All_Dir(char ch)
{
    if((ch == 's' || ch == KEY_DOWN))
    {
        orientation = 3;
    }else if((ch == 'w' || ch == KEY_UP))
    {
        orientation = 1;
    }else if((ch == 'd' || ch == KEY_RIGHT))
    {
        orientation = 2;
    }else if((ch == 'a' || ch == KEY_LEFT))
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
    }else if(head().row >= HEIGHT && orientation == 3)
    {
        return true;
    }else if(head().col >= WIDTH && orientation == 2)
    {
        return true;
    }else if(head().col <= 0 && orientation == 4)
    {
        return true;
    }
    return false;
}
