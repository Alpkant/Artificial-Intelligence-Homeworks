// Author: Alperen Kantarcı
// 150140140
// Created on 11/3/18.
// In order to compile following command should be executed
// g++ -std=c++11 main.cpp Action.cpp Node.cpp


#ifndef PEG_SOLITAIRE_ACTION_H
#define PEG_SOLITAIRE_ACTION_H

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

class Action {
public:
    int x;
    int y;
    Direction direction;
    // Default Constructor
    Action(int x, int y, Direction dir);
    // Empty constructor
    Action();
    // Copy constructor
    Action(const Action &parent);
};


#endif //PEG_SOLITAIRE_ACTION_H
