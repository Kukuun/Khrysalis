#pragma once

#include "Khrysalis/Layers/Layer.h"
#include "Khrysalis/Events/Event.h"

namespace Khrysalis {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

	private:
		bool _blockingEvents = true;
	};
}