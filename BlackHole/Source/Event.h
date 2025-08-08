#pragma once
#include <Windows.h>
#include <string>

class Event {
public:
	enum Type {
		NONE = 0,
		closed,
		keyDown,
		keyUp,
		mouseButtonDown,
		mouseButtonUp,
		mouseMove,
		mouseScroll
	};

	Type getType() const { return m_type; }
	
	virtual std::string toString() const = 0;

protected:
	Event() {}
	Type m_type = Type::NONE;

};

class KeyboardEvent : public Event {
public:
	virtual std::string toString() const override {}
	WPARAM getKeyCode() const { return m_keyCode; }
protected:
	KeyboardEvent(WPARAM _key) : m_keyCode (_key) {}

private:
	WPARAM m_keyCode;
};

class KeyDownEvent : public KeyboardEvent {
public:
	KeyDownEvent(WPARAM _key) : KeyboardEvent(_key) {
		m_type = Event::Type::keyDown;
	}
	std::string toString() const override {
		return "Key Pressed: " + std::to_string(getKeyCode());
	}
};

class KeyUpEvent : public KeyboardEvent {
public:
	KeyUpEvent(WPARAM _key) : KeyboardEvent(_key) {
		m_type = Event::Type::keyDown;
	}
	std::string toString() const override {
		return "Key Released: " + std::to_string(getKeyCode());
	}
};

class MouseButtonEvent : public Event {
public:
	virtual std::string toString() const {}
	WPARAM getButtonCode() const { return m_button; }
protected:
	MouseButtonEvent(WPARAM _button) : m_button(_button){}
private:
	WPARAM m_button;
};

class MouseButtonPressed : public MouseButtonEvent {
public:
	MouseButtonPressed(WPARAM _key) : MouseButtonEvent(_key) {
		m_type = Event::Type::mouseButtonDown;
	}
	std::string toString() const override {
		return "Mouse Button Pressed: " + std::to_string(getButtonCode());
	}
};

class MouseButtonReleased : public MouseButtonEvent {
public:
	MouseButtonReleased(WPARAM _key) : MouseButtonEvent(_key) {
		m_type = Event::Type::mouseButtonUp;
	}
	std::string toString() const override {
		return "Mouse Button Released: " + std::to_string(getButtonCode());
	}
};

class MouseMoved : public Event {
public:
	MouseMoved(float _x, float _y) : m_x(_x), m_y(_y) {
		m_type = Event::Type::mouseMove;
	}
	std::string toString() const override {
		return "Mouse Moved: " + std::to_string(m_x) + ", " + std::to_string(m_y);
	}
private:
	float m_x, m_y;
};

class MouseScrolled : public Event {
public:
	MouseScrolled(float _x, float _y) : m_x(_x), m_y(_y) {
		m_type = Event::Type::mouseMove;
	}
	std::string toString() const override {
		return "Mouse Scrolled: " + std::to_string(m_x) + ", " + std::to_string(m_y);
	}
private:
	float m_x, m_y;
};