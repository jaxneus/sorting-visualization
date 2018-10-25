#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <mutex>
#include <condition_variable>

// Full state of the application
public struct State {
	public static std::mutex pause_holder;
};

public struct AnimationState {
	public int time;
	public int speed;
	public bool paused;
	public std::vector<int> array;
	public std::vector<sf::Color> colors;
};