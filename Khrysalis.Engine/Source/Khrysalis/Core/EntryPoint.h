#pragma once

#include "Khrysalis/Core/Base.h"

#ifdef KAL_PLATFORM_WINDOWS

extern Khrysalis::Application* Khrysalis::CreateApplication();

int main(int argc, char** argv) {
	Khrysalis::Log::Initialize();

	auto* application = Khrysalis::CreateApplication();
	
	application->Run();

	delete application;
}

#endif