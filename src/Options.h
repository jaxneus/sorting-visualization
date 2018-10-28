#pragma once

struct Options {
	enum AlgorithmType algorithmType;
	enum Order order;
};

enum AlgorithmType {
	bubble_sort
};

enum Order {
	Shuffled,
	Ascending,
	Reversed
};
