#include "KalPch.h"
#include "Khrysalis/Inputs/Input.h"
#include "Khrysalis/Core/Application.h"

#include <glfw/glfw3.h>

namespace Khrysalis {
	bool Input::IsKeyPressed(KeyCode keyCode) {
		auto* window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, static_cast<int16_t>(keyCode));

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode mouseCode) {
		auto* window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, static_cast<int16_t>(mouseCode));

		return state == GLFW_PRESS;
	}

	Vector2 Input::GetMousePosition() {
		auto* window = Application::Get().GetWindow().GetNativeWindow();
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { (float)x, (float)y };
	}

	float Input::GetMouseX() {
		return GetMousePosition().X;
	}

	float Input::GetMouseY() {
		return GetMousePosition().Y;
	}
}