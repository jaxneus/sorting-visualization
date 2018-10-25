#include "Application.h"

int main() {
	Application application("sorting-visualization", 1280, 720);
	application.init();
	application.run();

	return 0;
}