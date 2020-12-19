#pragma once

#include "Khrysalis/Events/Event.h"

struct GLFWwindow;

namespace Khrysalis {
	struct WindowProps {
		std::string Title;
		int16_t Width;
		int16_t Height;

		WindowProps(const std::string& title = "Khrysalis",
			int16_t width = 1280,
			int16_t height = 720)
			: Title(title), Width(width), Height(height) {}
	};

	class Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window(const WindowProps& properties);
		~Window();

		void Initialize(const WindowProps& properties);
		void OnUpdate();

		void SetEventCallback(const EventCallbackFn& callback) { _data.EventCallback = callback; }
		void SetVSync(bool enabled);
		bool IsVSync() const;

		void CenterWindow();
		void Shutdown();

		GLFWwindow* GetNativeWindow() const { return _window; }

		int16_t GetWidth() const { return _data.Width; }
		int16_t GetHeight() const { return _data.Height; }

	private:
		GLFWwindow* _window;

		struct WindowData {
			std::string Title;
			int16_t Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData _data;

		uint16_t _minWidth = 720;
		uint16_t _minHeight = 540;
	};
}