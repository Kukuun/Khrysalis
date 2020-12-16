#pragma once

#include <Khrysalis.h>

class GameLayer : public Khrysalis::Layer {
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float deltaTime) override;
	void OnEvent(Khrysalis::Event& event) override;
};