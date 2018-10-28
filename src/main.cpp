#include "Application.h"

int main() {
	Application application("sorting-visualization", 1280, 720);

	Options options;
	options.algorithmType = AlgorithmType::bubble_sort;
	options.order = Order::Shuffled;
	application.init(options);

	return 0;
}