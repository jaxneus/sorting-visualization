#include "Application.h"

Application::Application(std::string title, uint width, uint height) 
	: m_title(title), m_width(width), m_height(height), NUM_BARS(width/5) {

}

Application::~Application() {}

void Application::Run() {
	sf::RenderWindow window(sf::VideoMode(m_width, m_height), m_title);

}