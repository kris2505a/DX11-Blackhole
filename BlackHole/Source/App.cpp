#include "App.h"

App::App() : m_window (nullptr) {
	m_window = new Window();
}

App::~App() {
	delete m_window;
}

void App::run() {
    while (m_window->isOpen()) {
        m_window->peekMessage();
    }
}
