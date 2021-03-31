// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <imgui/imgui.h>
#include <functional>
#include <span>

#include "EditorWindow.h"
#include "Gameplay/GameObject.h"
#include "Gameplay/ComponentHelper.h"
#include "Core/Maths/Vector3.h"

namespace Reality::Editor {
	class EditorInspector : public EditorWindow {
	public:
		void Draw(std::span<GameObject*> objects);

	private:
		template<class T>
		void Draw(std::function<void(T&)> func, T& comp) requires std::derived_from<T, Component>;

		void DrawName(GameObject& object);
		void DrawComponents(GameObject& object);
		void DrawAddComponent(GameObject& object);
		static void DrawTransform(CTransform& transform);
		static void DrawLight(CLight& light);
		static void DrawCamera(CCamera& camera);
		static void DrawMeshRenderer(CMeshRenderer& mesh);
	};
}

inline void Reality::Editor::EditorInspector::Draw(std::span<GameObject*> objects) {
	ImGui::Begin("Inspector");
	{
		if (!objects.empty()) {
			auto& object{ *objects.back() };
			DrawName(object);
			DrawComponents(object);

			if (ImGui::Button("Add Component", { -1.f, 0.f })) {
				ImGui::OpenPopup("AddComponentPopup");
			}

			if (ImGui::BeginPopup("AddComponentPopup")) {
				DrawAddComponent(object);
				ImGui::EndPopup();
			}
		}
	}
	ImGui::End();
}

template<class T>
void Reality::Editor::EditorInspector::Draw(std::function<void(T&)> func, T& comp) requires std::derived_from<T, Component> {
	if (ImGui::TreeNodeEx(rttr::type::get<T>().get_name().data(),
		ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding)) {
		ImGui::SameLine(ImGui::GetWindowWidth() - 30.f);
		if (ImGui::Button("+")) {
			ImGui::OpenPopup("ComponentSettings");
		}
		func(comp);

		if (ImGui::BeginPopup("ComponentSettings")) {
			if (ImGui::MenuItem("Remove")) {
				comp.GetGameObject().RemoveComponent<T>();
			}
			else if (ImGui::MenuItem("Reset")) {
				comp.Reset();
			}
			ImGui::EndPopup();
		}
		ImGui::TreePop();
	}
}

inline void Reality::Editor::EditorInspector::DrawName(GameObject& object) {
	ImGui::Checkbox("##IsActive", &object.IsActive);

	char buf[256]{};
	strcpy_s(buf, sizeof(buf), object.Name.c_str());

	ImGui::SameLine();
	if (ImGui::InputText("Name", buf, sizeof(buf))) {
		object.Name = buf;
	}
}

inline void Reality::Editor::EditorInspector::DrawComponents(GameObject& object) {
	DrawTransform(object.Transform);

	if (auto light{ object.GetComponent<CLight>() }) {
		Draw<CLight>(DrawLight, *light);
	}
	if (auto camera{ object.GetComponent<CCamera>() }) {
		Draw<CCamera>(DrawCamera, *camera);
	}
	if (auto mesh{ object.GetComponent<CMeshRenderer>() }) {
		Draw<CMeshRenderer>(DrawMeshRenderer, *mesh);
	}
}

inline void Reality::Editor::EditorInspector::DrawAddComponent(GameObject& object) {
	for (auto& type : rttr::type::get<Component>().get_derived_classes()) {
		if (ImGui::MenuItem(type.get_name().data())) {
			object.AddComponent(*type.get_method("Instantiate").invoke({}).convert<Component*>());
		}
	}
}

inline void Reality::Editor::EditorInspector::DrawTransform(CTransform& transform) {
	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_FramePadding)) {
		ImGui::SameLine(ImGui::GetWindowWidth() - 30.f);
		if (ImGui::Button("+")) {
			ImGui::OpenPopup("TransformSettings");
		}

		auto p{ transform.GetPosition() }, r{ transform.GetRotation().GetEulerAngles() }, s{ transform.GetScale() };
		if (ImGui::DragFloat3("Position", &p.X, .02f)) {
			transform.SetPosition(p);
		}
		if (ImGui::DragFloat3("Rotation", &r.X, .5f)) {
			transform.Rotate(-(r - transform.GetRotation().GetEulerAngles()));
		}
		if (ImGui::DragFloat3("Scale", &s.X, .005f)) {
			transform.SetScale(s);
		}

		if (ImGui::BeginPopup("TransformSettings")) {
			if (ImGui::MenuItem("Reset")) {
				transform.Reset();
			}
			ImGui::EndPopup();
		}
		ImGui::TreePop();
	}
}

inline void Reality::Editor::EditorInspector::DrawLight(CLight& light) {
	ImGui::Combo("Type", reinterpret_cast<int*>(&light.Type), "Directional\0Point\0Spot");
	ImGui::Combo("Shadow", reinterpret_cast<int*>(&light.Shadow), "None\0Soft");
	ImGui::ColorEdit4("Color", &light.Color.X);
	ImGui::DragFloat("Intensity", &light.Intensity, 0.005f, 0.f, 1.f);
	ImGui::DragFloat("Range", &light.Range, 0.05f, 0.f, 50.f);
	ImGui::DragFloat("SpotAngle", &light.SpotAngle, 0.5f, 0.f, 70.f);
}

inline void Reality::Editor::EditorInspector::DrawCamera(CCamera& camera) {
	ImGui::Combo("Clear flag", reinterpret_cast<int*>(&camera.Flag), "Skybox\0SolidColor\0DepthOnly\0DontClear");
	ImGui::Combo("Projection", reinterpret_cast<int*>(&camera.ProjectionType), "Perspective\0Orthographic");
	ImGui::DragFloat("Fov", &camera.Fov, 1.f, 1.f, 180.f);
	ImGui::DragFloat("Near", &camera.Near, 0.01f, 0.0001f, 10.f);
	ImGui::DragFloat("Far", &camera.Far, 1.f, 0.1f, 1000.f);
	if (camera.ProjectionType == CCamera::Projection::Orthographic) {
		ImGui::DragFloat("Ortho Size", &camera.OrthoSize);
	}
	ImGui::DragInt("Depth", &camera.Depth, 1.f, -100, 100);
}

inline void Reality::Editor::EditorInspector::DrawMeshRenderer(CMeshRenderer& mesh) {
	if (ImGui::BeginCombo("##Models", mesh.GetName().data())) {
		for (auto& [name, model] : g_ResourceManager->Models.GetResources()) {
			if (ImGui::Selectable(name.c_str())) {
				mesh.SetModel(name);
			}
		}
		ImGui::EndCombo();
	}
}