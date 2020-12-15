#include "KalPch.h"
#include "Khrysalis/Core/Application.h"
#include "Khrysalis/Debug/Log.h"
#include "Khrysalis/Events/ApplicationEvent.h"

namespace Khrysalis {
	Application* Application::Instance = nullptr;

	Application::Application(const std::string& name, const Version& version) : _name(name), _version(version) {
		Instance = this;

		_window = std::make_unique<Window>(WindowProps());
		_window->SetEventCallback(KAL_BIND_EVENT_FN(Application::OnEvent));
	}

	void Application::Run() {
		while (_running) {
			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(KAL_BIND_EVENT_FN(Application::OnWindowsClose));
	}

	bool Application::OnWindowsClose(WindowCloseEvent& event) {
		_running = false;
		return true;
	}

	bool Application::OnWindowsResize(WindowResizeEvent& event) {
		if (event.GetWidth() == 0 || event.GetHeight() == 0) {
			_minimized = true;
			return false;
		}

		_minimized = false;

		return true;
	}
}