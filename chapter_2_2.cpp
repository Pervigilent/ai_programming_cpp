/*
 * Edited By: Stewart Nash
 * Date: October 2020
 * Description: C++ implementation of depth-first search
 * 	algorithm.
 */
#include "chapter_2.h"
#include <iostream>
#include <assert.h>

bool adjacentNodes[NODE_COUNT][NODE_COUNT];
bool visitedNodes[NODE_COUNT];

const int STACK_MAXIMUM = 10;

int stack[STACK_MAXIMUM];

int stackIndex;

void initializeMatrices() {
	for (int i = 0; i < NODE_COUNT; i++) {
		visitedNodes[i] = false;
		for (int j = 0; j < NODE_COUNT; j++) {
			adjacentNodes[i][j] = false;
		}
	}
}

void makeEdge(int startNode, int endNode) {
	assert(startNode < NODE_COUNT && endNode < NODE_COUNT);
	assert(startNode >= 0 && endNode >= 0);

	adjacentNodes[startNode][endNode] = true;
	//std::cout << "Adjacency matrix (" << startNode << ", ";
	//std::cout << endNode << ") = " << adjacentNodes[startNode][endNode];
	//std::cout << std::endl;
}

void initializeStack() {
	stackIndex = 0;
}

void push(int element) {
	assert(stackIndex < STACK_MAXIMUM);

	stack[stackIndex++] = element;
}

int pop() {
	int element;

	assert(stackIndex > 0);

	element = stack[--stackIndex];

	return element;
}

bool isEmpty() {
	if (stackIndex == 0) {
		return true;
	} else {
		return false;
	}
}

void depthFirstSearch(int start, int goal) {
	int node;

	push(start);
	while (!isEmpty()) {
		// Open a new node.
		node = pop();
		
		if (node == goal) {
			std::cout << node << " goal reached." << std::endl;
			return;
		}


		if (visitedNodes[node]) {
			//continue;
		} else {
			visitedNodes[node] = true;
			std::cout << node << "\t";
			// Push each of the children of the current node onto the stack.
			for (int i = NODE_COUNT - 1; i >= 0; i--) {
				//std::cout << "Read adjacent node (" << node << ", ";
				//std::cout << i << ") = " << adjacentNodes[node][i];
				//std::cout << std::endl;
				if (adjacentNodes[node][i]) {
					push(i);
					//std::cout << "pushing " << i << std::endl;
				}
			}
		}
	}
	std::cout << "Goal not found." << std::endl;
}

int test_2_2() {
	initializeMatrices();
	initializeStack();
	// Build our graph in the adjacency matrix.
	makeEdge(1, 2);
	makeEdge(1, 3);
	makeEdge(1, 4);
	makeEdge(2, 5);
	makeEdge(3, 5);
	makeEdge(3, 6);
	makeEdge(4, 7);
	makeEdge(5, 8);
	makeEdge(5, 9);

	depthFirstSearch(1, 6);
	
	return 0;
}
