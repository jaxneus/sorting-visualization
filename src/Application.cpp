#include "Application.h"
#include "Algorithm.h"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>
#include <thread>

Application::Application(std::string title, uint width, uint height) 
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width/5) {

}

Application::~Application() {}

void Application::init() {
	m_array = std::vector<int>(NUM_BARS);

	state.anim.time = 0.0;
	state.anim.speed = 0;
	state.anim.paused = true;
	state.anim.array = m_array;
	state.anim.colors = std::vector<sf::Color>(m_array.size());

	// Populate and shuffle the array
	for (int i = 0; i < NUM_BARS; i++)
		m_array[i] = (rand() % 10) + 1;

	std::random_shuffle(m_array.begin(), m_array.end());

	// Print the arrays contents before sort
	for (auto i = m_array.begin(); i != m_array.end(); ++i)
		std::cout << *i << ' ';
	printf("\n");


	BubbleSort alg = BubbleSort();
	printf("Running algorthim: %s \n", alg.name(state).c_str());
	alg.sort(state, m_array);
}

void Application::run() {
	sf::RenderWindow m_window(sf::VideoMode(m_width, m_height), m_title);

	m_sorted = false;
	while (m_window.isOpen()) {
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		
		m_window.clear();

		update();
		render(m_array);

		for (int i = 0; i < NUM_BARS; i++) {
			m_window.draw(visualize_value(i, sf::Color::White));
		}

		if (!m_sorted) {

			printf("sorted: \n");
			for (auto i = m_array.begin(); i != m_array.end(); ++i)
				std::cout << *i << ' ';
			printf("\n");

			for (int i = 0; i < NUM_BARS; i++) {
				m_window.draw(visualize_value(i, sf::Color::White));

				m_window.display();
				std::this_thread::sleep_for(std::chrono::milliseconds(3));
			}
		}

		m_window.display();
	}
}

void Application::update() {}
void Application::render(std::vector<int> array) {}

void Application::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		std::lock_guard<std::mutex> lock(state.pause);
		state.anim.paused = !state.anim.paused;

		state.cv.notify_one();
	}
}

sf::RectangleShape Application::visualize_value(int index, sf::Color color) {
	int value = index;

	auto w = 5;
	auto h = value * m_height / NUM_BARS;
	auto x = value + 5 * value;
	auto y = m_height - h;

	sf::RectangleShape rec(sf::Vector2f(w, h));
	rec.setPosition(sf::Vector2f(x, y));
	rec.setFillColor(color);

	return rec;
}