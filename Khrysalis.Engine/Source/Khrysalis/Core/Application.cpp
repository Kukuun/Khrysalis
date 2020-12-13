#include "KalPch.h"
#include "Khrysalis/Core/Application.h"
#include "Khrysalis/Debug/Log.h"
#include "Khrysalis/Events/ApplicationEvent.h"

namespace Khrysalis {
	Application* Application::Instance = nullptr;

	Application::Application(const std::string& name, const Version& version) : _name(name), _version(version) {
		KAL_ENGINE_ASSERT(!Instance, "Application already exists.")

		Instance = this;
	}

	void Application::Run() {}
}