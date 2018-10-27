#include "Application.h"
#include "Algorithm.h"

#include "imgui/imgui.h"
#include "imgui/imgui-sfml.h"

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>
#include <thread>

Application::Application(std::string title, uint width, uint height)
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width / 5) {
}

Application::~Application() {}

void sortTask(Algorithm& alg, Array& arr) {
	// Print the arrays contents before sort
	arr.dump();

	arr.wait(50);
	if (alg.sort(arr)) {
		printf("%s has finished. \n", alg.name().c_str());
		arr.dump();

		return;
	}
}

/**
 *   -- TODO LIST --
 *  Store each array access step that way we can see history of the sort.
**/

void Application::init() {
	BubbleSort algorthim = BubbleSort();
	printf("Running algorthim: %s \n", algorthim.name().c_str());

	m_state.anim.time = 0.0;
	m_state.anim.speed = 0;
	m_state.anim.paused = false;
	m_state.anim.array = std::vector<int>(NUM_BARS);
	m_state.anim.colors = std::vector<sf::Color>(m_state.anim.array.size());

	std::vector<int>& arr = m_state.anim.array;

	// Populate and shuffle the array
	for (int i = 0; i < NUM_BARS - 1; i++)
		arr[i] = (rand() % 10) + 1;

	std::random_shuffle(arr.begin(), arr.end());

	std::thread al(sortTask, algorthim, Array(m_state));

	run(); // need to execute this here or else we block before running the window.

	al.join();
}

void Application::run() {
	sf::RenderWindow m_window(sf::VideoMode(m_width, m_height), m_title);
	ImGui::SFML::Init(m_window);

	sf::Color bgColor;

	float color[3] = { 0.f, 0.f, 0.f };

	m_sorted = false;

	double t = 0.0;
	const double dt = 0.0;

	auto ct = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	double accumulator = 0.0;

	m_window.resetGLStates();
	while (m_window.isOpen()) {
		auto now = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		double frameTime = now - ct;

		accumulator += frameTime;

		input();
		m_window.clear();

		for (int i = 0; i < NUM_BARS; i++) {
			m_window.draw(visualize_value(i, sf::Color::White));
		}

		while (!m_state.anim.paused) {
			while (accumulator >= dt) {
				// update()

				accumulator -= dt;
				t += dt;
			}

			ImGui::SFML::Update(m_window, sf::milliseconds(dt));

			ImGui::Begin("Sample window"); // begin window

			ImGui::Button("Look at this pretty button");

			ImGui::End();
			ImGui::SFML::Render(m_window);

			// render()
			if (!m_sorted) {
				for (int i = 0; i < NUM_BARS; i++) {
					m_window.draw(visualize_value(i, sf::Color::White));

					m_window.display();
					std::this_thread::sleep_for(std::chrono::milliseconds(3));
				}
			}
		}

		m_window.display();
	}

	ImGui::SFML::Shutdown();
}

void Application::update(double dt) {}
void Application::render() {}

void Application::input() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

		if (event.type == sf::Event::Closed)
			m_window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		std::lock_guard<std::mutex> lock(m_state.pause);
		m_state.anim.paused = !m_state.anim.paused;
		printf("anim.paused toggled \n");

		m_state.cv.notify_one();
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