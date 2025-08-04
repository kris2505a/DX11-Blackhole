#pragma once
#include <string>
#include <Windows.h>

struct Procs {
	unsigned int width;
	unsigned int height;
	Procs(unsigned int _width = 1600u, unsigned int _height = 900u)
		: width(_width), height(_height) { }
};

class Window {
public:
	Window();
	~Window();
	static LRESULT CALLBACK winProcHandler(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

private:
	Procs m_procs;
	
	HWND m_winHandle;
	WNDCLASSEX m_wClass;
	HINSTANCE m_instance;

private:
	void initWinClass();
	void initHandle();
};

