// Author: Alperen Kantarcı
// 150140140
// Created on 11/3/18.
// In order to compile following command should be executed
// g++ -std=c++11 main.cpp Action.cpp Node.cpp



#ifndef PEG_SOLITAIRE_NODE_H
#define PEG_SOLITAIRE_NODE_H

#include <iostream>
#include <vector>
#include "Action.h"

#define HEIGHT 7
#define WIDTH 7

using namespace std;

class Node {
public:
    vector<vector<int>> board;
    int number_of_peg = -1;
    int depth = -1;
    Action action = Action();
    Node *parent = NULL;
    int heuristic = -1;
    int heuristic_type = -1;

    Node(const int new_depth, const Action past_action, Node *parent_node); // Constructor with action and parent
    Node(); // Empty constructor
    Node(const Node &old); // Copy constructor

    void initial_node(int type = -1);

    vector<vector<int>> make_move(const vector<vector<int>> parent_board);
    // Print the state with beautified version
    void print_state();

    bool check_goal_state();

    bool check_move_valid(Action move);

    int calculate_heuristic();

    vector<Node> expand();

    // These operators for  Priority queue
    friend bool operator<(const Node &left, const Node &right);

    friend bool operator>(const Node &left, const Node &right);

};


#endif //PEG_SOLITAIRE_NODE_H
