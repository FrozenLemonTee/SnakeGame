#ifndef ARENA_H
#define ARENA_H

#include <vector>
#include <list>

class Arena{
private:
    int width;
    int height;
    std::vector<std::vector<int>> matrix;
public:
    Arena(int w, int h);
    int& mat(int row, int col);
};

class SnakeNode{
public:
    SnakeNode(int row, int col);
    int row;
    int col;
    void copyNode(SnakeNode next);
    SnakeNode moveUp();
    SnakeNode moveDown();
    SnakeNode moveLeft();
    SnakeNode moveRight();
};

class Snake{
public:
    int orientation;
    Snake(int row, int col, int ori);
    std::list<SnakeNode> body;
    SnakeNode head();
    void update();
    void increase();
    void listen(char ch);
    int size();
};




#endif