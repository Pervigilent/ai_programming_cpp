/*
 * File: jones_chapter_3.cpp
 * Author: Stewart Nash
 * Date: December 14, 2020
 * Description: C++ realization of simulated annealing
 * example of AI text by M Tim Jones.
 *
 */
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

class MemberType {
public:
	std::vector<int> solution;
	double energy;
	double computeEnergy();
};

double MemberType::computeEnergy() {
	double output;
	std::vector<std::vector<char>> board;
	int conflicts;
	const int BOARD_LENGTH = this->solution.size();

	for (int j = 0; j < BOARD_LENGTH; j++) {
		std::vector<char> temporary;
		for (int i = 0; i < BOARD_LENGTH; i++) {
			temporary.push_back(0);
		}
		board.push_back(temporary);
		board[j][solution[j]] = 'Q';
	}

	conflicts = 0;
	for (int i = 0; i < BOARD_LENGTH; i++) {
		int currentX, currentY;
		int xLocation, yLocation;
		const int tempX[4] = { -1, 1, -1 , 1 };
		const int tempY[4] = { -1 , 1, 1, -1 };
		currentX = i;
		currentY = solution[i];
		for (int j = 0; j < 4; j++) {
			xLocation = currentX + tempX[j];
			yLocation = currentY + tempY[j];
			if (xLocation >= 0 &&
				yLocation >= 0 &&
				xLocation < BOARD_LENGTH &&
				yLocation < BOARD_LENGTH) {
				if (board[xLocation][yLocation] == 'Q') {
					++conflicts;
				}
			}
		}
	}

	output = static_cast<double>(conflicts);
	this->energy = output;

	return output;
}

const int DEFAULT_BOARD_SIZE = 30;

void tweakSolution(MemberType& member);
void initializeSolution(MemberType &member);
void copySolution(const MemberType& input, MemberType& output);
void emitSolution(MemberType& member);

int main(int argc, char* argv[]) {
	const double INITIAL_TEMPERATURE = 30;
	const double FINAL_TEMPERATURE = 0.5;
	const double ALPHA = 0.99;
	const int STEPS_PER_CHANGE = 100;

	MemberType current, working, best;
	double temperature;
	int timer;
	int step;
	bool solution;
	int accepted;
	bool useNew;

	srand((unsigned)time(NULL));
	initializeSolution(current);
	initializeSolution(best);
	copySolution(current, working);
	solution = false;
	temperature = INITIAL_TEMPERATURE;
	timer = 0;

	while (temperature > FINAL_TEMPERATURE) {
		std::cout << "Temperature: " << temperature << std::endl;
		accepted = 0;
		for (step = 0; step < STEPS_PER_CHANGE; step++) {
			useNew = true;
			tweakSolution(working);
			if (working.computeEnergy() < current.computeEnergy()) {
				useNew = true;
			} else {
				double test;
				double delta;
				double calc;

				test = rand() / RAND_MAX;
				delta = working.computeEnergy() - current.computeEnergy();
				calc = exp(-delta / temperature);
				if (calc > test) {
					accepted++;
					useNew = true;
				}
			}

			if (useNew) {
				useNew = false;
				copySolution(working, current);
				if (current.computeEnergy() < best.computeEnergy()) {
					copySolution(current, best);
					solution = true;
				}
			} else {
				copySolution(current, working);
			}
		}

		std::cout << "Time: " << timer++; 
		std::cout << ", temperature: " << temperature;
		std::cout << ", best energy: " << best.computeEnergy();
		std::cout << ", accepted: " << accepted;
		std::cout << std::endl;

		temperature *= ALPHA;
	}

	if (solution) {
		emitSolution(best);
	}

	return 0;
}

void tweakSolution(MemberType& member) {
	//int x, y;
	int a, b;
	int temporary;
	const int BOARD_LENGTH = member.solution.size();

	a = rand() % BOARD_LENGTH;
	do {
		b = rand() % BOARD_LENGTH;
	} while (a == b);

	temporary = member.solution[a];
	member.solution[a] = member.solution[b];
	member.solution[b] = temporary;
}

void initializeSolution(MemberType &member) {
	const int BOARD_LENGTH = DEFAULT_BOARD_SIZE;
	// Initial setup of the solution
	for (int i = 0; i < BOARD_LENGTH; i++) {
		member.solution.push_back(i);
	}
	// Randomly perturb the solution
	for (int i = 0; i < BOARD_LENGTH; i++) {
		tweakSolution(member);
	}
}

void copySolution(const MemberType& input, MemberType& output) {
	output.solution.clear();
	for (int i = 0; i < input.solution.size(); i++) {
		output.solution.push_back(input.solution[i]);
	}
	output.energy = input.energy;
}

void emitSolution(MemberType& member) {
	std::vector<std::vector<char>> board;

	for (int i = 0; i < member.solution.size(); i++) {
		std::vector<char> temporary;
		for (int j = 0; j < member.solution.size(); j++) {
			if (member.solution[i] == j) {
				temporary.push_back('Q');
			} else {
				temporary.push_back('.');
			}
		}
		board.push_back(temporary);
	}

	// Why create and then print? Why not print simultaneously and omit array?
	std::cout << std::endl;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			std::cout << board[i][j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

