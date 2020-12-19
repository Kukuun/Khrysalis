#include "EditorLayer.h"

#include <imgui/imgui.h>

namespace Khrysalis {
	EditorLayer::EditorLayer() : Layer("EditorLayer") {}

	void EditorLayer::OnAttach() {
		KAL_TRACE("EditorLayer::OnAttach");
	}

	void EditorLayer::OnDetach() {
		KAL_TRACE("EditorLayer::OnDetach");
	}

	void EditorLayer::OnUpdate(float deltaTime) {
		//KAL_TRACE("{0:.3f} m/s", deltaTime * 1000);
	}

	void EditorLayer::OnImGuiRender() {
		static bool dockspaceOpen = true;
		static bool isFullscreenPersistant = true;
		bool isFullscreen = isFullscreenPersistant;
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (isFullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("DockSpace Demo", &dockspaceOpen, windowFlags);
		ImGui::PopStyleVar();

		if (isFullscreen)
			ImGui::PopStyleVar(2);

		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 200.f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Close"))
					Application::Get().Close();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Viewport");
		ImGui::End();

		ImGui::Begin("Hierarchy");
		ImGui::End();

		ImGui::Begin("Properties");
		ImGui::End();

		ImGui::Begin("Content Browser");
		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event) {
		//KAL_TRACE("Event: {0}", event);
	}
}