#include "Application.h"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>
#include <thread>

Application::Application(std::string title, uint width, uint height) 
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width/5) {

}

Application::~Application() {}

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
			m_array = std::vector<int>(NUM_BARS);
			for (int i = 0; i < NUM_BARS; i++)
				m_array[i] = (rand() % 10) + 1;

			std::random_shuffle(m_array.begin(), m_array.end());

			for (auto i = m_array.begin(); i != m_array.end(); ++i)
				std::cout << *i << ' ';
			printf("\n");

			std::vector<int> done = bubble_sort(m_array);

			printf("sorted: \n");
			for (auto i = done.begin(); i != done.end(); ++i)
				std::cout << *i << ' ';
			printf("\n");

			m_sorted = true;

			for (int i = 0; i < NUM_BARS; i++) {
				m_window.draw(visualize_value(i, sf::Color::White));

				m_window.display();
				std::this_thread::sleep_for(std::chrono::milliseconds(3));
			}
		}

		m_window.display();
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

void Application::update() {}
void Application::render(std::vector<int> array) {}

std::vector<int> Application::bubble_sort(std::vector<int>& arr) {
	unsigned int size_of_array = arr.size() - 1;

	for (unsigned int i = 0; i < size_of_array; i++) {
		bool swapped = false;
		for (unsigned int j = 0; j < size_of_array; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(j, j + 1);
				swapped = true;
			}
		}

		if (!swapped) break;
	}

	return arr;
}

void Application::swap(int firstIndex, int secondIndex) {
	int temp = m_array[firstIndex];
	m_array[firstIndex] = m_array[secondIndex];
	m_array[secondIndex] = temp;
}