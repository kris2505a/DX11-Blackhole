#pragma once
#include "Window.h"

class App {
public:
	App();
	~App();

	void run();
	void onEvent(Event& e);

private:
	Window* m_window;
};