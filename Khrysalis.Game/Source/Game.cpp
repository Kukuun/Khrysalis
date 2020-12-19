#pragma once

#include <Khrysalis.h>
#include <Khrysalis/Core/EntryPoint.h>

#include "GameLayer.h"

class Game : public Khrysalis::Application {
public:
	Game() : Application("App") {
		PushOverlay(new GameLayer());
	}

	~Game() {}
};

Khrysalis::Application* Khrysalis::CreateApplication() {
	return new Game();
}