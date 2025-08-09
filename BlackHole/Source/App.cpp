#include "App.h"
#include <iostream>
#include <fstream>



App::App() : m_window (nullptr) {
	m_window = new Window();
    m_window->setCallbackFn(std::bind(&App::onEvent, this, std::placeholders::_1));
}

App::~App() {
	delete m_window;
}

void App::onEvent(Event& e) {
    std::cout << e.toString() << std::endl;
}

void App::run() {
    while (m_window->isOpen()) {
        m_window->peekMessage();
        update(1.0f);
        render();
    }
}

void App::update(float deltaTime) {

}

void App::render() {
    
}