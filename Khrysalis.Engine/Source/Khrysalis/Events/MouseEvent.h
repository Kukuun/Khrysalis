#pragma once

#include "Khrysalis/Events/Event.h"
#include "Khrysalis/Inputs/MouseCodes.h"

namespace Khrysalis {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(const float x, const float y) : _mouseX(x), _mouseY(y) {}

		float GetX() const { return _mouseX; }
		float GetY() const { return _mouseY; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float _mouseX, _mouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

		float GetXOffset() const { return _xOffset; }
		float GetYOffset() const { return _yOffset; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseScrolledEvent: " << _xOffset << ", " << _yOffset;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float _xOffset, _yOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		MouseCode GetMouseButton() const { return _button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(const MouseCode button) : _button(button) {}

		MouseCode _button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(const MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseButtonPressedEvent: " << _button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(const MouseCode mouseCode) : MouseButtonEvent(mouseCode) {}

		std::string ToString() const override {
			std::stringstream stream;
			stream << "MouseButtonReleasedEvent: " << _button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}