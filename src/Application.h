#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

typedef unsigned int uint;

class Application {
private:
	sf::RenderWindow m_window;

	std::string m_title;
	uint m_width;
	uint m_height;
	bool m_sorted;

	std::vector<int> m_array;
public:
	Application(std::string title, uint width, uint height);
	~Application();

	const int NUM_BARS;

	void run();
	void update();
	void render(std::vector<int> array);

	sf::RectangleShape visualize_value(int index, sf::Color color);
	
	std::vector<int> bubble_sort(std::vector<int>& numbers_to_sort);
	void swap(int firstIndex, int secondIndex);

};
