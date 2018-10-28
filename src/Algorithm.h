#pragma once

#include "State.h"
#include "Array.h"
#include "Options.h"

#include <vector>
#include <string>

class Algorithm {
public:
	virtual bool sort(Array& array) { return false; };
	virtual const std::string name() { return "nullptr"; };
};

class BubbleSort : public Algorithm {
public:
	bool sort(Array& array) override {
		unsigned int size_of_array = array.len() - 1;

		printf("Starting a sort. \n");
		for (unsigned int i = 0; i < size_of_array; i++) {
			bool swapped = false;
			for (unsigned int j = 0; j < size_of_array; j++) {
				if (array[j] > array[j + 1]) {
					array.swap(j, j + 1);
					swapped = true;
				}
			}

			if (!swapped) break;
		}

		printf("Finished a sort. \n");
		array.dump();
		return true;
	};

	const std::string name() override {
		return "Bubble sort";
	};
};

class SelectionSort : public Algorithm {
public:
	bool sort(Array& array) override {
		int i, j;
		unsigned int size_of_array = array.len() - 1;

		printf("Starting a sort. \n");
		for (j = 0; j < size_of_array - 1; j++) {
			int iMin = j;

			for (i = j + 1; i < size_of_array; i++) {
				if (array[i] < array[iMin]) {
					iMin = i;
				}
			}

			if (iMin != j) {
				array.swap(j, iMin);
			}
		}

		printf("Finished a sort. \n");
		array.dump();
		return true;
	};

	const std::string name() override {
		return "Selection sort";
	};
};