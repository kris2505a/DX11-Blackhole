#pragma once
#include "Window.h"

class App {
public:
	App();
	~App();

	void run();

private:
	Window* m_window;
};