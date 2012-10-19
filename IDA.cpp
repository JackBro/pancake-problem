//
//  IDA.cpp
//  pancake-problem
//
//  Created by Grace Gimon on 06/10/12.
//  Copyright (c) 2012 Grace Gimon. All rights reserved.
//

#include <iostream>
#include <vector>
#include "IDA.h"
#include "Node.h"

using namespace std;

    // Stack where the already visited nodes reside
    vector<Node> closed;
    
    // Termination bound
    int bound = 1000000000;
    
    int w;

    Solution::Solution() {
        solved = false;
    }

Solution boundedDFS(Node n, int t){
    Solution solution;
    
    // Checks if the bound hasn't been reached
    int sum = n.getG() + (n.getH()*w);
    if (sum > t) {
        solution.cost = sum;
        return solution;
    }
    
    // Check if there is a solution
    if (n.isGoal()) {
        solution.cost = n.getG();
        solution.solved = true;
        cout << "Solved: " << solution.cost << endl;
        return solution;
    }
    
    int newT = bound;
    
    for (int i = 2; i != n.getNumPancakes() + 1; ++i) {
        Node suc = n.getSuccesor(i);
        
        // If this succesor already exists, continue
     /*   if (find(closed.begin(), closed.end(), suc) != closed.end())
            continue;
        
        closed.push_back(suc);*/
        
        Solution aux = boundedDFS(suc, t);
        
        if (aux.solved) {
            aux.plan.push_back(i);
            return aux;
        }
        
        newT = min(newT, aux.cost);
    }

    // There is no succesor that reachs the goal
    solution.cost = newT;
    return solution;
}

Solution ida(Node n, int weight) {
    Solution solution;
    solution.cost = n.getH()*weight;
    w = weight;
    while (!solution.solved && solution.cost < bound) {
    //while(!solution.solved){
      //  stack = vector<Node>(1, n);
        solution = boundedDFS(n, solution.cost);
    }
    
    return solution;
}
