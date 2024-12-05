#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <list>


class Arena{
private:
    int width;
    int height;
    //matrix stores the declaration value
    std::vector<std::vector<int>> matrix;
public:
    Arena(int w, int h);
    //Interface of matrix, not really necessary though
    int& mat(int row, int col);
    void insertFood(int row, int col);
    void deleteFood(int row, int col);
};

class SnakeNode{
public:
    //SnakeNode is a piece of the Snake
    SnakeNode(int row, int col);
    int row;
    int col;
    //Function to copy a Node to another
    void copyNode(SnakeNode next);
    //Function that returns a new Node in different orientation
    SnakeNode moveUp();
    SnakeNode moveDown();
    SnakeNode moveLeft();
    SnakeNode moveRight();
};

class Snake{
public:
    //orientation of the head node
    int orientation;
    Snake(int row, int col, int ori);
    //Use double linked list to store the body of the Snake
    std::list<SnakeNode> body;
    //Function that returns the head node
    SnakeNode head();
    //Function that moves the snake
    void update();
    //Function that increases the length of the snake
    void increase(int num);
    //Function that checks whether touching the border
    bool border();
    //Value that indicates how many length should our Snake increase
    int INCREASE;
    //Function that processes the Keyboard input
    void listen(char ch);
    //Function taht returns the length of our Snake
    int size();
};


#endif