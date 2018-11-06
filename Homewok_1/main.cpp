// Author: Alperen Kantarcı
// 150140140
// Created on 11/3/18.
// In order to compile following command should be executed
// g++ -std=c++11 main.cpp Action.cpp Node.cpp


#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <algorithm>
#include <cstring>

#include "Action.h"
#include "Node.h"

using namespace std;
long generated_nodes = 0;
long expanded_nodes = 0;
long max_kept_nodes = 0;

#define HEIGHT 7
#define WIDTH 7

Node BFS(Node &root_of_tree) {
    queue<Node> frontier;
    frontier.push(root_of_tree);
    while (!frontier.empty()) {
        Node current = frontier.front();
        frontier.pop();
        if (current.check_goal_state()) {
            current.print_state();
            return current;
        }

        vector<Node> successors = current.expand();
        expanded_nodes++;
        generated_nodes += successors.size();
        for (int i = 0; i < successors.size(); i++) {
            frontier.push(successors[i]);
        }
        if (frontier.size() > max_kept_nodes) {
            max_kept_nodes = frontier.size();
        }
    }
    return Node();
}

Node DFS(Node &root_of_tree) {
    stack<Node> frontier;
    frontier.push(root_of_tree);
    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();
        if (current.check_goal_state()) {
            current.print_state();
            return current;
        }
        vector<Node> successors = current.expand();
        expanded_nodes++;
        generated_nodes += successors.size();
        for (int i = 0; i < successors.size(); i++) {
            frontier.push(successors[i]);
        }
        if (frontier.size() > max_kept_nodes) {
            max_kept_nodes = frontier.size();
        }
    }
    return Node();

}

// Heuristic 1 is heuristic 1 which is number of pegs that have any move

Node A_star(Node &root_of_tree, int heuristic) {
    priority_queue<Node> frontier;
    frontier.push(root_of_tree);
    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();
        if (current.check_goal_state()) {
            current.print_state();
            return current;
        }
        vector<Node> successors = current.expand();
        expanded_nodes++;
        generated_nodes += successors.size();
        for (int i = 0; i < successors.size(); i++) {
            frontier.push(successors[i]);
        }
        if (frontier.size() > max_kept_nodes) {
            max_kept_nodes = frontier.size();
        }
    }
    return Node();

}


int main(int argc, char **argv) {
    if (argc < 1) {
        cerr << "You need to give one of the following command line arguments: bfs dfs astar" << endl;
        return 0;
    }

    Node root_of_tree = Node();
    clock_t tStart, tFinish;
    Node solution;
    cout << argv[1];
    if (!strcmp(argv[1], "dfs")) {

        root_of_tree.initial_node();
        tStart = clock();
        solution = DFS(root_of_tree);

    } else if (!strcmp(argv[1], "bfs")) {

        root_of_tree.initial_node();
        tStart = clock();
        solution = BFS(root_of_tree);

    } else if (!strcmp(argv[1], "astar1")) {
        // Create node with heuristic
        root_of_tree.initial_node(1);
        tStart = clock();
        solution = A_star(root_of_tree, 1);

    } else if (!strcmp(argv[1], "astar2")) {

        root_of_tree.initial_node(2);
        tStart = clock();
        solution = A_star(root_of_tree, 2);

    } else {
        cerr << "You have given wrong argument." << endl;
        return 0;
    }

    tFinish = clock();
    double time = (tFinish - tStart) / double(CLOCKS_PER_SEC) * 100;
    cout << "Time: " << time << " ms" << endl;
    if (solution.depth == -1) {
        cout << "Solution couldn't found." << endl;
        return 0;
    }
    cout << "Remaining number of pegs: " << solution.number_of_peg << endl;
    cout << "Depth of the solution: " << solution.depth << endl;
    cout << "Number of Generated nodes: " << generated_nodes << endl;
    cout << "Number of Expanded nodes: " << expanded_nodes << endl;
    cout << "Maximum number of nodes kept in memory: " << max_kept_nodes << endl;


    return 0;
}