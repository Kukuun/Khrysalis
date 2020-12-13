#pragma once

#include "Khrysalis/Events/Event.h"

namespace Khrysalis {
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : _width(width), _height(height) {}

		uint32_t GetWidth() { return _width; }
		uint32_t GetHeight() { return _height; }

		std::string ToString() const override {
			std::stringstream stream;
			stream << "WindowResizeEvent: " << _width << ", " << _height;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		uint32_t _width, _height;
	};

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ApplicationTickEvent : public Event {
	public:
		ApplicationTickEvent() = default;

		EVENT_CLASS_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ApplicationUpdateEvent : public Event {
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class ApplicationRenderEvent : public Event {
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_TYPE(ApplicationRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
