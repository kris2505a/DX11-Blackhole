#include "Window.h"


Window::Window() {
	m_instance = GetModuleHandle(nullptr);
	initWinClass();
	initHandle();
	ShowWindow(m_winHandle, SW_SHOW);
	m_open = true;
}

Window::~Window() {
	UnregisterClass(L"BlackholeWindow", m_instance);
	DestroyWindow(m_winHandle);
}

LRESULT Window::winProcHandler(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam) {

	Window* window = nullptr;

	if (_msg == WM_NCCREATE) {
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(_lparam);
		window = static_cast<Window*>(create->lpCreateParams);
		SetWindowLongPtr(_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
	}
	else {
		window = reinterpret_cast<Window*>(GetWindowLongPtr(_hwnd, GWLP_USERDATA));
	}

	switch (_msg) {
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		window->m_open = false;
	}break;
	}
	
	return DefWindowProc(_hwnd, _msg, _wparam, _lparam);
}

void Window::initWinClass() {
	m_wClass = { 0 };
	m_wClass.cbSize = sizeof(WNDCLASSEX);
	m_wClass.style = CS_OWNDC;
	m_wClass.lpfnWndProc = winProcHandler;
	m_wClass.cbClsExtra = 0;
	m_wClass.cbWndExtra = 0;
	m_wClass.hInstance = m_instance;
	m_wClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);  
	m_wClass.hCursor = LoadCursor(nullptr, IDC_ARROW);    
	m_wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  
	m_wClass.lpszMenuName = nullptr;
	m_wClass.lpszClassName = L"BlackholeWindow";
	m_wClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	UnregisterClass(L"BlackholeWindow", m_instance);
	RegisterClassEx(&m_wClass);

}

void Window::initHandle() {
	m_winHandle = CreateWindowEx(
		0,
		L"BlackholeWindow",
		L"BlackHole",
		WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION,
		100, 100,
		m_procs.width, m_procs.height,
		nullptr,
		nullptr,
		m_instance,
		this
	);
	if (!m_winHandle) {
		DWORD err = GetLastError();
		MessageBoxA(nullptr, ("CreateWindowEx failed. Error code: " + std::to_string(err)).c_str(), "Error", MB_OK | MB_ICONERROR);
	}

}

bool Window::isOpen() const {
	return m_open;
}

void Window::peekMessage() {
	MSG msg = {};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}