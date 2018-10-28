#include "Application.h"
#include "Algorithm.h"

#include "imgui/imgui.h"
#include "imgui/imgui-sfml.h"

#include <SFML/Window/Event.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

#define BAR_WIDTH 8

std::shared_ptr<Algorithm> getClassByType(AlgorithmType type) {
	switch (type) {
	case AlgorithmType::bubble_sort:
		return std::shared_ptr<Algorithm>(new BubbleSort());
	case AlgorithmType::selection_sort:
		return std::shared_ptr<Algorithm>(new SelectionSort());
	}
}

Application::Application(std::string title, uint width, uint height)
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width / BAR_WIDTH) {
}

Application::~Application() {}

/**
 *   -- TODO LIST --
 *  Store each array access step that way we can see history of the sort.
 *  PRIORITY -- Setup README.md for git and setup project description on Github
 *  Global program options, choice for order of array (ascending, reversed, shuffled)
**/

bool m_sorted = false;
void Application::init(Options& options) {
	auto algorthim = getClassByType(options.algorithmType);
	printf("Running algorthim: %s \n", algorthim->name().c_str());

	m_state.anim.time = 0.0;
	m_state.anim.speed = 1;
	m_state.anim.paused = false;
	m_state.anim.array = std::vector<int>(NUM_BARS);
	m_state.anim.colors = std::vector<sf::Color>(NUM_BARS);

	std::vector<int>& array = m_state.anim.array;
	std::vector<sf::Color>& colors = m_state.anim.colors;

	// Populate and shuffle the array
	for (int i = 0; i < NUM_BARS; i++) {
		array[i] = i;
		colors[i] = sf::Color::White;
	}

	switch (options.order) {
	case Shuffled:
		std::random_shuffle(array.begin(), array.end());
		break;
	case Ascending:
		break;
	case Reversed:
		std::reverse(array.begin(), array.end());
		break;
	}

	Array arr = Array(m_state);
	std::thread al([&algorthim, &arr] {
		// Print the arrays contents before sort
		arr.dump();

		arr.wait(250 * 5);
		if (algorthim->sort(arr)) {
			m_sorted = true;

			return;
		}
	});

	run();
	al.join();
}

void Application::run() {
	sf::RenderWindow m_window(sf::VideoMode(m_width, m_height), m_title);
	ImGui::SFML::Init(m_window);

	sf::Clock deltaClock;
	auto beginTime = std::chrono::high_resolution_clock::now();

	glViewport(0 + 50, 0 + 50, m_width - 50, m_height - 50);
	while (m_window.isOpen()) {
		auto dt = deltaClock.restart().asSeconds();
		auto now = std::chrono::high_resolution_clock::now();

		input();
		sf::Event event;
		while (m_window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				m_window.close();
		}

		update(dt);

		// GUI
		ImGui::SFML::Update(m_window, sf::milliseconds(dt));
		ImGui::Begin("Settings (imgui)"); // begin window

		ImGui::Button("Pretty button!");

		ImGui::End();

		ImGui::ShowDemoWindow();
		ImGui::EndFrame();
		render(m_window);
	}

	ImGui::SFML::Shutdown();
	return;
}

void Application::update(double dt) {
	auto anim = m_state.anim;

	if (!anim.paused)
		anim.time += dt * anim.speed;
}

void Application::render(sf::RenderWindow& window) {
	window.clear();
	for (int i = 0; i < m_state.anim.array.size(); i++) {
		window.draw(visualize_value(i, sf::Color::White));
		ImGui::SFML::Render(m_window);
	}

	// Overlay for array acceses
	if (!m_sorted) {
		for (int i = 0; i < m_state.anim.array.size(); i++) {
			window.draw(visualize_value(i, m_state.anim.colors[i]));
			window.display();
			ImGui::SFML::Render(m_window);
		}
	}

	window.display();
	ImGui::SFML::Render(m_window);
}

void Application::input() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		std::lock_guard<std::mutex> lock(m_state.pause);
		m_state.anim.paused = !m_state.anim.paused;
		printf("anim.paused toggled \n");

		m_state.cv.notify_one();
	}
}

sf::RectangleShape Application::visualize_value(int index, sf::Color color) {
	int value = m_state.anim.array[index];

	auto w = BAR_WIDTH;
	auto h = value * m_height / NUM_BARS;
	auto x = index * w;
	auto y = m_height - h;

	sf::RectangleShape rec(sf::Vector2f(w - 1, h));
	rec.setPosition(sf::Vector2f(x, y));
	rec.setFillColor(color);

	return rec;
}