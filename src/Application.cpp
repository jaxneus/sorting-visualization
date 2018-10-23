#include "Application.h"

#include <SFML/Window/Event.hpp>
#include <iostream>

Application::Application(std::string title, uint width, uint height) 
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width/5) {

}

Application::~Application() {}

void Application::run() {
	sf::RenderWindow m_window(sf::VideoMode(m_width, m_height), m_title);

	m_array = std::vector<int>(NUM_BARS);
	for (int i = 0; i < NUM_BARS; i++)
		m_array[i] = (rand() % 10) + 1;

	std::random_shuffle(m_array.begin(), m_array.end());

	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		
		m_window.clear();

		update();
		render(m_array);

		for (int i = 0; i < m_array.size(); i++) {
			sf::RectangleShape val = visualize_value(i, sf::Color::White);
			m_window.draw(val);
		}

		m_window.display();
	}
}

sf::RectangleShape Application::visualize_value(uint index, sf::Color color) {
	auto value = m_array[index];

	auto w = m_width / m_array.size();
	auto h = value * m_height / NUM_BARS;
	auto x = value * w;
	auto y = m_height - h;

	printf("%d width, %d height, %d x, %d y \n", w, h, x, y);

	sf::RectangleShape rec(sf::Vector2f(w, h));
	rec.setPosition(sf::Vector2f(x, y));
	rec.setFillColor(color);

	return rec;
}

void Application::update() {}
void Application::render(std::vector<int> array) {}