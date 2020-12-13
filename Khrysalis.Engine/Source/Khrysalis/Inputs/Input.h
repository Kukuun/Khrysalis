#pragma once

#include "Khrysalis/Inputs/KeyCodes.h"
#include "Khrysalis/Inputs/MouseCodes.h"

namespace Khrysalis {
	class Input {
		static bool IsKeyPressed(KeyCode keyCode);

		static bool IsMouseButtonPressed(MouseCode mouseCode);
		static float GetMouseX();
		static float GetMouseY();
	};
}