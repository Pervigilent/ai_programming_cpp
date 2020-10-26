/*
 * Edited By: Stewart Nash
 * Date: October 2020
 * Description: C++ implementation of breadth-first search
 * 	algorithm.
 */
#include "chapter_2.h"
#include <iostream>
#include <assert.h>

const int QUEUE_MAXIMUM = 10;

int queue[QUEUE_MAXIMUM];
int read, write;

inline int Wrap(int input) {
	return ((input == QUEUE_MAXIMUM - 1) ? 0 : input + 1);
}

void initializeQueue() {
	write = 0;
	read = 0;
}

bool isQueueEmpty() {
	if (write == read) {
		return true;
	} else {
		return false;
	}
}

void enqueue(int element) {
	queue[write] = element;
	write = Wrap(write);
}

int dequeue() {
	int element;

	assert(!isQueueEmpty());
	element = queue[read];
	read = Wrap(read);

	return element;
}

void breadthFirstSearch(int start, int goal) {
	int node;

	enqueue(start);
	while (!isQueueEmpty()) {
		// Open a new node.
		node = dequeue();
		
		if (node == goal) {
			std::cout << node << " goal reached." << std::endl;
			return;
		}


		if (visitedNodes[node]) {
			//continue;
		} else {
			visitedNodes[node] = true;
			std::cout << node << "\t";
			// Enqueue each of the children of the current node onto the queue.
			for (int i = 0; i < NODE_COUNT; i++) {
				if (adjacentNodes[node][i]) {
					enqueue(i);
				}
			}
		}
	}
	std::cout << "Goal not found." << std::endl;
}

int test_2_3() {
	initializeMatrices();
	initializeQueue();

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

	breadthFirstSearch(1, 9);
	
	return 0;
}
