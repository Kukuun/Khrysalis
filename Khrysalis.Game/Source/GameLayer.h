#pragma once

#include <Khrysalis.h>

class GameLayer : public Khrysalis::Layer {
public:
	GameLayer();
	virtual ~GameLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnEvent(Khrysalis::Event& event) override;
	virtual void OnImGuiRender() override;
};