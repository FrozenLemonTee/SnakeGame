#include <Arena.hpp>
#include <vector>
#include "curses.h"
#include "data.hpp"


Arena::Arena(const int w, const int h): width(w), height(h), matrix(h, std::vector<int>(w,0)) {}

int& Arena::mat(const int row, const int col)
{
    return matrix[row][col];
}

void Arena::insertFood(const int row, const int col)
{
    if(matrix[row][col] == 0)
    {
        matrix[row][col] = 1;
    }
}

void Arena::deleteFood(const int row, const int col)
{
    if(matrix[row][col] == 1)
    {
        matrix[row][col] = 0;
    }
}

void Arena::insertObs(const int row, const int col)
{
    if(matrix[row][col] == 0)
    {
        matrix[row][col] = -2;
    }
}


SnakeNode::SnakeNode(const int row, const int col): row{row}, col{col} {}

void SnakeNode::copyNode(const SnakeNode next)
{
    //You can also define the operator= to implement this function
    row = next.row;
    col = next.col;
}


//These function returns a new node in different orientation
SnakeNode SnakeNode::moveUp() const
{
    return {row-1, col};
}

SnakeNode SnakeNode::moveDown() const
{
    return {row+1, col};
}

SnakeNode SnakeNode::moveLeft() const
{
    return {row, col-1};
}

SnakeNode SnakeNode::moveRight() const
{
    return {row, col+1};
}


Snake::Snake(const int row, const int col, const int ori): orientation{ori}, INCREASE(0)
{
    body.emplace_front(row, col);
}

SnakeNode Snake::head() const
{
    return body.front();
}

int Snake::size() const
{
    return body.size(); // converting type size_t(aka unsigned long long) to type int is not appropriate ^_^
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
        //If I have INCREASE, I don't want to pop back
        return false;
    }
    return true;
}

void Snake::listen(const char ch)
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
    }
}

void Snake::listen_All_Dir(const char ch)
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
    }
}

void Snake::increase(const int num)
{
    INCREASE += num;
}

bool Snake::border() const
{
    if(head().row <= 0 && orientation == 1)
    {
        return true;
    }
    if(head().row >= HEIGHT && orientation == 3)
    {
        return true;
    }
    if(head().col >= WIDTH && orientation == 2)
    {
        return true;
    }
    if(head().col <= 0 && orientation == 4)
    {
        return true;
    }
    return false;
}
