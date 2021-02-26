#include "KalPch.h"
#include "Khrysalis/Core/Application.h"
#include "Khrysalis/Debug/Log.h"
#include "Khrysalis/Events/ApplicationEvent.h"

#include "Khrysalis/Graphics/Renderer.h"
#include "Khrysalis/Graphics/D3D/D3D11Renderer.h"

#include <glfw/glfw3.h>

namespace Khrysalis {
	Application* Application::Instance = nullptr;

	Application::Application(const std::string& name, const Version& version) : _name(name), _version(version) {
		Instance = this;

		_window = std::make_unique<Window>(WindowProps());
		_window->SetEventCallback(KAL_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Initialize();

		_imguiLayer = new ImGuiLayer();
		PushOverlay(_imguiLayer);
	}

	Application::~Application() {
		Renderer::Shutdown();
	}

	void Application::Run() {
		while (_running) {
			float time = (float)glfwGetTime();
			float deltaTime = time - _lastFrameTime;
			_lastFrameTime = time;

			if (!_minimized) {
				for (Layer* layer : _layerStack) {
					layer->OnUpdate(deltaTime);
				}

				_imguiLayer->Begin();

				for (Layer* layer : _layerStack) {
					layer->OnImGuiRender();
				}

				_imguiLayer->End();
			}

			_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(KAL_BIND_EVENT_FN(Application::OnWindowsClose));
		dispatcher.Dispatch<WindowResizeEvent>(KAL_BIND_EVENT_FN(Application::OnWindowsResize));

		for (auto iterator = _layerStack.end(); iterator != _layerStack.begin(); ) {
			if (event.Handled) {
				break;
			}

			(*--iterator)->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer) {
		_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
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

	void Application::Close() {
		_running = false;
	}
}