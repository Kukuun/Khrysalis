#pragma once

#include "Khrysalis/Maths/Vector2.h"
#include "Khrysalis/Inputs/KeyCodes.h"
#include "Khrysalis/Inputs/MouseCodes.h"

namespace Khrysalis {
	class Input {
		static bool IsKeyPressed(const KeyCode keyCode);

		static bool IsMouseButtonPressed(const MouseCode mouseCode);
		static Vector2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}