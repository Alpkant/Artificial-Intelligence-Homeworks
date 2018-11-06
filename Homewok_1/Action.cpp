// Author: Alperen Kantarcı
// 150140140
// Created on 11/3/18.
// In order to compile following command should be executed
// g++ -std=c++11 main.cpp Action.cpp Node.cpp



#include "Action.h"


Action::Action() {

}

Action::Action(int x, int y, Direction dir) {
    this->x = x;
    this->y = y;
    this->direction = dir;
}

Action::Action(const Action &parent) {
    this->x = parent.x;
    this->y = parent.y;
    this->direction = parent.direction;
}
