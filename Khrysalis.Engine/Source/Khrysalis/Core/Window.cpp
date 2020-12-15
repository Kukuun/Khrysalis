#include "KalPch.h"
#include "Khrysalis/Core/Window.h"
#include "Khrysalis/Events/ApplicationEvent.h"
#include "Khrysalis/Events/KeyEvent.h"
#include "Khrysalis/Events/MouseEvent.h"

#include <glfw/glfw3.h>

namespace Khrysalis {
	Window::Window(const WindowProps& properties) {
		Initialize(properties);
	}

	Window::~Window() {
		Shutdown();
	}

	void Window::Initialize(const WindowProps& properties) {
		_data.Title = properties.Title;
		_data.Width = properties.Width;
		_data.Height = properties.Height;

		KAL_ENGINE_INFO("Creating window {0} ({1}, {2})", _data.Title, _data.Width, _data.Height);

		int success = glfwInit();
		KAL_ENGINE_ASSERT(success, "Could not initialize GLFW.");

		glfwSetErrorCallback([](int error, const char* description) {
			KAL_ENGINE_ERROR("GLFW error ({0}): {1}", error, description);
		});

		_window = glfwCreateWindow(_data.Width, _data.Height, _data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(_window);
		glfwSetWindowUserPointer(_window, &_data);
		SetVSync(true);

		glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.EventCallback(e);
		});

		CenterWindow();
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(_window);
	}

	void Window::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		_data.VSync = enabled;
	}

	bool Window::IsVSync() const {
		return _data.VSync;
	}

	void Window::CenterWindow() {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		KAL_ENGINE_ASSERT(monitor, "Could not get primary monitor.");

		const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
		KAL_ENGINE_ASSERT(videoMode, "Could not get video mode.");

		int monitorX, monitorY;
		glfwGetMonitorPos(monitor, &monitorX, &monitorY);

		int windowWidth, windowHeight;
		glfwGetWindowSize(_window, &windowWidth, &windowHeight);

		glfwSetWindowPos(_window, monitorX + (videoMode->width - windowWidth) / 2, monitorY + (videoMode->height - windowHeight) / 2);
	}

	void Window::Shutdown() {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}
}