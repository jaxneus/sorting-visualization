#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <atomic>

#include "State.h"
#include "Array.h"

typedef unsigned int uint;

class Application {
private:
	sf::RenderWindow m_window;

	std::string m_title;
	uint m_width;
	uint m_height;

	State m_state;
public:
	Application(std::string title, uint width, uint height);
	~Application();

	const int NUM_BARS;

	void init();
	void run();

	void input();

	void update(double dt);
	void render(sf::RenderWindow& window);

	sf::RectangleShape visualize_value(int index, sf::Color color);
};
