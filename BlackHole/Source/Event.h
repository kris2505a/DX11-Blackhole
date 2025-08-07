#pragma once
#include <Windows.h>

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

protected:
	Event() {}
	Type m_type = Type::NONE;

};

class KeyboardEvent : public Event {
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
};

class KeyUpEvent : public KeyboardEvent {
public:
	KeyUpEvent(WPARAM _key) : KeyboardEvent(_key) {
		m_type = Event::Type::keyDown;
	}
};