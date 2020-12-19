#pragma once

#include <Khrysalis.h>
#include <Khrysalis/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Khrysalis {
	class Editor : public Khrysalis::Application {
	public:
		Editor() : Application("Editor") {
			PushOverlay(new EditorLayer());
		}

		~Editor() {}
	};

	Khrysalis::Application* Khrysalis::CreateApplication() {
		return new Editor();
	}
}