#pragma once

#include "Khrysalis/Events/Event.h"

namespace Khrysalis {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return _name; }

	protected:
		std::string _name;
	};
}