// Author: Alperen Kantarcı
// 150140140
// Created on 11/3/18.
// In order to compile following command should be executed
// g++ -std=c++11 main.cpp Action.cpp Node.cpp


#include "Node.h"


Node::Node() {

}

Node::Node(const int new_depth, const Action past_action, Node *parent_node) {
    number_of_peg = parent_node->number_of_peg;
    depth = new_depth;
    action = past_action;
    parent = parent_node;
    board = make_move(parent_node->board);
    heuristic_type = parent_node->heuristic_type;
    heuristic = calculate_heuristic();
}

Node::Node(const Node &old) {
    this->board = old.board;
    this->number_of_peg = old.number_of_peg;
    this->depth = old.depth;
    this->action = old.action;
    this->parent = old.parent;
    this->heuristic = old.heuristic;
    this->heuristic_type = old.heuristic_type;
}

// -1 is outside 0 is empty 1 is peg
// Initial board is
/*  0  0 1  1 1  0  0
    0  0 1  1 1  0  0
    1  1 1  1 1  1  1
    1  1 1 -1 1  1  1
    1  1 1  1 1  1  1
    0  0 1  1 1  0  0
    0  0 1  1 1  0  0

*/

void Node::initial_node(int type) {
    board = {
            {0, 0, 1, 1,  1, 0, 0},
            {0, 0, 1, 1,  1, 0, 0},
            {1, 1, 1, 1,  1, 1, 1},
            {1, 1, 1, -1, 1, 1, 1},
            {1, 1, 1, 1,  1, 1, 1},
            {0, 0, 1, 1,  1, 0, 0},
            {0, 0, 1, 1,  1, 0, 0}
    };
    depth = 0;
    number_of_peg = 32;
    heuristic_type = type;
    heuristic = calculate_heuristic();
}

vector<vector<int>> Node::make_move(const vector<vector<int>> parent_board) {
    vector<vector<int>> newboard = parent_board;
    int x = action.x;
    int y = action.y;
    if (action.direction == UP) {
        newboard[x][y] = -1;
        newboard[x - 1][y] = -1;
        newboard[x - 2][y] = 1;
    } else if (action.direction == DOWN) {
        newboard[x][y] = -1;
        newboard[x + 1][y] = -1;
        newboard[x + 2][y] = 1;
    } else if (action.direction == LEFT) {
        newboard[x][y] = -1;
        newboard[x][y - 1] = -1;
        newboard[x][y - 2] = 1;
    } else {
        newboard[x][y] = -1;
        newboard[x][y + 1] = -1;
        newboard[x][y + 2] = 1;
    }
    number_of_peg--;
    return newboard;
}

void Node::print_state() {
    cout << "Dots (.) are peg and circles (o) are empty spaces " << endl;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // If out of board print empty space
            if (board[i][j] == 0)
                cout << "  ";
                // if peg then print dot(.)
            else if (board[i][j] == 1)
                cout << ". ";
                // if its empty space then print o
            else cout << "o ";
        }
        cout << endl;
    }
}

bool Node::check_goal_state() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // Check if there is a move at up
            if (i - 2 >= 0) {
                if (board[i][j] == 1 && board[i - 1][j] == 1 && board[i - 2][j] == -1)
                    return false;
            }
            // Check if there is a move at down
            if (i + 2 < HEIGHT) {
                if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == -1)
                    return false;
            }
            // Check if there is a move at left
            if (j - 2 >= 0) {
                if (board[i][j] == 1 && board[i][j - 1] == 1 && board[i][j - 2] == -1)
                    return false;
            }
            // Check if there is a move at right
            if (j + 2 < WIDTH) {
                if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == -1)
                    return false;
            }
        }
    }
    // Couldn't find any move so it's goal
    return true;
}

bool Node::check_move_valid(Action move) {
    int x = move.x;
    int y = move.y;
    switch (move.direction) {
        case UP:
            if (x - 2 >= 0) {
                if (board[x][y] == 1 && board[x - 1][y] == 1 && board[x - 2][y] == -1)
                    return true;
            }
            break;

        case DOWN:
            if (x + 2 < HEIGHT) {
                if (board[x][y] == 1 && board[x + 1][y] == 1 && board[x + 2][y] == -1)
                    return true;
            }
            break;

        case LEFT:
            if (y - 2 >= 0) {
                if (board[x][y] == 1 && board[x][y - 1] == 1 && board[x][y - 2] == -1)
                    return true;
            }
            break;

        case RIGHT:
            if (y + 2 < WIDTH) {
                if (board[x][y] == 1 && board[x][y + 1] == 1 && board[x][y + 2] == -1)
                    return true;
            }
            break;
    }

    return false;
}


int Node::calculate_heuristic() {

    int tmp = 0;
    // If type is -1 then heuristic is not important so no need to calculate
    if (heuristic_type == -1)
        return --tmp;
        // If heuristic type == 1 (possible number of moves)
    else if (heuristic_type == 1) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board[i][j] == 1) {
                    Action up = Action(i, j, UP);
                    Action down = Action(i, j, DOWN);
                    Action left = Action(i, j, LEFT);
                    Action right = Action(i, j, RIGHT);

                    if (this->check_move_valid(up))
                        tmp++;
                    if (this->check_move_valid(down))
                        tmp++;
                    if (this->check_move_valid(left))
                        tmp++;
                    if (this->check_move_valid(right))
                        tmp++;
                }
            }
        }

    } else if (heuristic_type == 2) {
        // This heuristic is number of pegs that can move
        // Lower the number is better for the goal state
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (board[i][j] == 1) {
                    Action up = Action(i, j, UP);
                    Action down = Action(i, j, DOWN);
                    Action left = Action(i, j, LEFT);
                    Action right = Action(i, j, RIGHT);

                    // If peg can make any move then increase heuristic by one
                    if (this->check_move_valid(up) || this->check_move_valid(down)
                        || this->check_move_valid(left) || this->check_move_valid(right)) {
                        tmp++;
                    }

                }
            }
        }
    }
    return tmp;
}


vector<Node> Node::expand() {
    vector<Node> leaves = vector<Node>();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == 1) {
                Action up = Action(i, j, UP);
                Action down = Action(i, j, DOWN);
                Action left = Action(i, j, LEFT);
                Action right = Action(i, j, RIGHT);

                if (this->check_move_valid(up))
                    leaves.push_back(Node(depth + 1, up, this));
                if (this->check_move_valid(down))
                    leaves.push_back(Node(depth + 1, down, this));
                if (this->check_move_valid(left))
                    leaves.push_back(Node(depth + 1, left, this));
                if (this->check_move_valid(right))
                    leaves.push_back(Node(depth + 1, right, this));
            }
        }
    }
    return leaves;
}

// Since we want least cost more prioritized this operators overloading
// gives more priority to smaller heuristic value

bool operator>(const Node &left, const Node &right) {
    return (left.heuristic + left.depth) < (right.heuristic + right.depth);
}

bool operator<(const Node &left, const Node &right) {
    return (left.heuristic + left.depth) > (right.heuristic + right.depth);
}


