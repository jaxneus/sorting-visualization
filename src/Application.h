#pragma once

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
public:
	Application(std::string title, uint width, uint height);
	~Application();

	const int NUM_BARS;

	void Run();
	void Update();
	void Render();
};
