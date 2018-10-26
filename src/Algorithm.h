#pragma once

#include "State.h"
#include "Array.h"

#include <vector>
#include <string>

class Algorithm {
public:
	void sort(std::vector<int>& array) {};
	const std::string name(State& state) { return ""; };
};

class BubbleSort : public Algorithm {
public:
	void sort(Array& array) {
		unsigned int size_of_array = array.len();

		for (unsigned int i = 0; i < size_of_array; i++) {
			bool swapped = false;
			for (unsigned int j = 0; j < size_of_array; j++) {
				if (array[j] > array[j+1]) {
					array.swap(j, j + 1);
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