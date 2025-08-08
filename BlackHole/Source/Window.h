#pragma once
#include <string>
#include <Windows.h>
#include <functional>
#include "Event.h"

struct Procs {
	unsigned int width;
	unsigned int height;
	Procs(unsigned int _width = 1600u, unsigned int _height = 900u)
		: width(_width), height(_height) { }
};

class Window {
	using EventCallbackFn = std::function<void(Event&)>;
public:
	Window();
	~Window();
	static LRESULT CALLBACK winProcHandler(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	bool isOpen() const;
	void peekMessage();
	void setCallbackFn(const EventCallbackFn& fn);

private:
	Procs m_procs;
	
	HWND m_winHandle;
	WNDCLASSEX m_wClass;
	HINSTANCE m_instance;

	EventCallbackFn m_callback;
	bool m_open;

private:
	void initWinClass();
	void initHandle();
};

