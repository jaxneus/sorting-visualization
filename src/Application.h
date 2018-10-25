#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "State.h"

typedef unsigned int uint;

class Application {
private:
	sf::RenderWindow m_window;

	std::string m_title;
	uint m_width;
	uint m_height;
	bool m_sorted;

	std::vector<int> m_array;
	State state;
public:
	Application(std::string title, uint width, uint height);
	~Application();

	const int NUM_BARS;

	void init();

	void run();
	void update();
	void render(std::vector<int> array);
	void input();

	sf::RectangleShape visualize_value(int index, sf::Color color);
};
