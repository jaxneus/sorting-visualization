#pragma once

#include "State.h"

#include <vector>
#include <string>

class Algorithm {
public:
	void sort(State& state, std::vector<int>& array) {};
	const std::string name(State& state) { return ""; };
};

inline void swap(std::vector<int> array, int firstIndex, int secondIndex) {
	int temp = array[firstIndex];
	array[firstIndex] = array[secondIndex];
	array[secondIndex] = temp;
};

class BubbleSort : public Algorithm {
public:
    void sort(State& state, std::vector<int>& array) {
		unsigned int size_of_array = array.size() - 1;

		for (unsigned int i = 0; i < size_of_array; i++) {
			bool swapped = false;
			for (unsigned int j = 0; j < size_of_array; j++) {
				if (array[j] > array[j + 1]) {
					swap(array, j, j + 1);
					swapped = true;
				}
			}

			if (!swapped) break;
		}
	};

	const std::string name(State& state) {
		return "Bubble sort";
	};
};