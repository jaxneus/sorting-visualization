#pragma once
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <mutex>
#include <condition_variable>

struct AnimationState {
	int time;
	int speed;
	bool paused;
	std::vector<int> array;
	std::vector<sf::Color> colors;
};

// Full state of the application
struct State {
	std::mutex pause;
	std::condition_variable cv;
	
	AnimationState anim;
};