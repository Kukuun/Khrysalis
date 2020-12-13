#pragma once

#include <Khrysalis.h>
#include <Khrysalis/Core/EntryPoint.h>

class Game : public Khrysalis::Application {
public:
	Game() : Application("App") {
		KAL_INFO(__FUNCSIG__);
	}

	~Game() {
		KAL_INFO(__FUNCSIG__);
	}
};

Khrysalis::Application* Khrysalis::CreateApplication() {
	return new Game();
}
