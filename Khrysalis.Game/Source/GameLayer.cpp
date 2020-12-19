#include "GameLayer.h"

GameLayer::GameLayer() : Layer("App") {}

void GameLayer::OnAttach() {
	KAL_TRACE("GameLayer::OnAttach");
}

void GameLayer::OnDetach() {
	KAL_TRACE("GameLayer::OnDetach");
}

void GameLayer::OnUpdate(float deltaTime) {
	//KAL_TRACE("{0:.3f} m/s", deltaTime * 1000);
}

void GameLayer::OnEvent(Khrysalis::Event& event) {
	KAL_TRACE("Event: {0}", event);
}

void GameLayer::OnImGuiRender() {
}