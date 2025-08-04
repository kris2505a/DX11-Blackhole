#include "App.h"

App::App() : m_window (nullptr) {
	m_window = new Window();
}

App::~App() {
	delete m_window;
}

void App::run() {
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
