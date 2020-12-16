#pragma once

#include "Khrysalis/Events/Event.h"
#include "Khrysalis/Inputs/KeyCodes.h"

namespace Khrysalis {
	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return _keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(const KeyCode keyCode) : _keyCode(keyCode) {}

		KeyCode _keyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keyCode, const int16_t repeatCount) : KeyEvent(keyCode), _repeatCount(repeatCount) {}

		std::string ToString() const override {
			std::stringstream stream;
			stream << "KeyPressedEvent" << _keyCode << " (" << _repeatCount << " repeats)";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int16_t _repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream stream;
			stream << "KeyReleasedEvent: " << _keyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(const KeyCode keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream stream;
			stream << "KeyTypedEvent: " << _keyCode;
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}