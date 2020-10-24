#include "chapter_2.h"
#include <iostream>
#include <assert.h>

const int NODE_COUNT = 10;
const int STACK_MAXIMUM = 10;

int adjacentNodes[NODE_COUNT][NODE_COUNT];
int visitedNodes[NODE_COUNT];
int stack[STACK_MAXIMUM];

int stackIndex;

void initializeMatrices() {
	for (int i = 0; i < NODE_COUNT; i++) {
		visitedNodes[i] = 0;
		for (int j = 0; j < NODE_COUNT; j++) {
			adjacentNodes[i][j] = 0;
		}
	}
}

void makeEdge(int startNode, int endNode) {
	assert(startNode < NODE_COUNT && endNode < NODE_COUNT);
	assert(startNode >= 0 && endNode >= 0);

	adjacentNodes[startNode][endNode] = 1;
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
			continue;
		} else {
			visitedNodes[node] = 1;
		}
		std::cout << node;
		// Push each of the children of the current node onto the stack.
		for (int i = NODE_COUNT - 1; i <= 0; i--) {
			if (adjacentNodes[node][i] == 1) {
				push(i);
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
