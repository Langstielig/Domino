#pragma once
#include <iostream>
#include <vector>

class Domino {

	std::vector<std::pair<int, int>> dominoSet;
	int count;

public:
	Domino() {
		count = 28;
		dominoSet.resize(28);
		int n = 0;
		for (int i = 0; i < 7; i++)
			for (int j = i; j < 7; j++) {
				dominoSet[n].first = i;
				dominoSet[n].second = j;
				n++;
			}
	}

	Domino(std::vector<std::pair<int, int>> a, int n) {
		count = n;
		dominoSet.resize(count);
		for (int i = 0; i < count; i++) {
			dominoSet[i].first = a[i].first;
			dominoSet[i].second = a[i].second;
		}
	}

	std::vector<std::pair<int, int>> getDominoSet() {
		return dominoSet;
	}

	int getCount() {
		return count;
	}

	void print() {
		for (int i = 0; i < count; i++)
			std::cout << "[" << dominoSet[i].first << ":" << dominoSet[i].second << "]" << " ";
	}
};
