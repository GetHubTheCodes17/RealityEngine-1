// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLParticleSystem.h"
#include "Rendering/Opengl/GLPipeline.h"
#include "Rendering/Opengl/GLMaterial.h"
#include "Rendering/Opengl/GLContext.h"
#include "Rendering/Opengl/GLLight.h"
#include "Rendering/Opengl/GLMesh.h"
#include "Rendering/Opengl/GLModel.h"
#include "ComponentHelper.h"
#include "Windowing/IO.h"
#include "Scene.h"

namespace Reality {
	class ComponentSystem {
	public:
		void UpdateTransforms(Scene& scene) const;
		void UpdateCameras(Scene& scene, Vector2 windowSize) const;
		void UpdateLights(Scene& scene) const;
		void UpdateMeshesShadow(Scene& scene) const;
		void UpdateMeshes(Scene& scene) const;
		void UpdateParticles(Scene& scene) const;
		void UpdateMonoBehaviours(Scene& scene) const;
	};
}

inline void Reality::ComponentSystem::UpdateTransforms(Scene& scene) const {
	std::function<void(CTransform&)> UpdateHierarchy = [&UpdateHierarchy](auto& root) {
		if (root.HasChanged()) {
			root.SetTrs(Matrix4::Scale(root.GetScale()) * root.GetRotation().GetMatrix() *
				Matrix4::Translate(root.GetPosition()));
		}

		if (const auto parent{ root.GetParent() }; parent && parent->HasChanged()) {
			root.SetTrs(root.GetTrs() * parent->GetTrs());
		}

		for (auto child : root.GetChildren()) {
			UpdateHierarchy(*child);
		}
		root.SetHasChanged(false);
	};

	for (const auto& object : scene.m_Roots) {
		UpdateHierarchy(object->Transform);
	}
}

inline void Reality::ComponentSystem::UpdateCameras(Scene& scene, Vector2 windowSize) const {
	for (const auto camera : scene.m_Manager.GetComponents<CCamera>()) {
		CCamera::s_Main = static_cast<const CCamera*>(camera);
	}
	if (CCamera::s_Main) {
		if (const auto transform{ CCamera::s_Main->GetGameObject().GetComponent<CTransform>() }; transform && transform->HasChanged()) {
			GLContext::SetProjectionMatrix(Matrix4::Perspective(windowSize.X / windowSize.Y, CCamera::s_Main->Near,
				CCamera::s_Main->Far, CCamera::s_Main->Fov));
			GLContext::SetViewMatrix(Matrix4::LookAt(transform->GetPosition(), transform->GetForward(), transform->GetUp()));
		}
	}
}

inline void Reality::ComponentSystem::UpdateLights(Scene& scene) const {
	if (auto lights{ scene.m_Manager.GetComponents<CLight>() }; !lights.empty()) {
		std::vector<GLLight> glLights(lights.size());
		for (std::size_t i{}; i < glLights.size(); ++i) {
			const auto& light{ *static_cast<const CLight*>(lights[i]) };
			glLights[i] = { 
				light.Color, light.GetGameObject().Transform.GetPosition(), 0, 
				light.GetGameObject().Transform.GetForward(), 0, (enum GLLight::Type)light.Type, 
				(enum GLLight::Shadow)light.Shadow, light.Intensity, light.Range - 10.f, light.SpotAngle 
			};

			if (light.Type == CLight::Type::Directional && light.Shadow == CLight::Shadow::Soft) {
				GLContext::SetShadowMatrix(glLights[i].Direction, {}, { -15.f, 15.f, -15.f, 15.f, -15.f, 15.f });
			}
		}
		GLContext::SetLights(glLights);
	}
}

inline void Reality::ComponentSystem::UpdateMeshesShadow(Scene& scene) const {
	for (const auto mesh : scene.m_Manager.GetComponents<CMeshRenderer>()) {
		if (mesh->GetGameObject().IsActive) {
			GLContext::SetModelMatrix(mesh->GetGameObject().Transform.GetTrs());
			if (const auto glModel{ static_cast<const CMeshRenderer*>(mesh)->GetModel() }) {
				for (const auto& glMesh : glModel->Meshes) {
					glMesh->Draw();
				}
			}
		}
	}
}

inline void Reality::ComponentSystem::UpdateMeshes(Scene& scene) const {
	for (const auto mesh : scene.m_Manager.GetComponents<CMeshRenderer>()) {
		if (mesh->GetGameObject().IsActive) {
			GLContext::SetModelMatrix(mesh->GetGameObject().Transform.GetTrs());
			if (const auto glModel{ static_cast<const CMeshRenderer*>(mesh)->GetModel() }) {
				for (const auto& glMesh : glModel->Meshes) {
					if (const auto glMaterial{ glMesh->Material }) {
						glMaterial->Bind();
					}
					glMesh->Draw();
				}
			}
		}
	}
}

inline void Reality::ComponentSystem::UpdateParticles(Scene& scene) const {
	for (const auto& system : scene.m_Manager.GetComponents<CParticleSystem>()) {
		if (const auto glSystem{ static_cast<const CParticleSystem*>(system)->System }) {
			glSystem->Direction = Vector3::Normalize(system->GetGameObject().Transform.GetForward());
			glSystem->Position = system->GetGameObject().Transform.GetPosition();
			if (auto camera{ CCamera::s_Main }) {
				glSystem->Update(g_Io->Time->GetDeltaTime() * glSystem->Speed, 
					camera->GetGameObject().Transform.GetPosition());
			}
		}
	}
}

inline void Reality::ComponentSystem::UpdateMonoBehaviours(Scene& scene) const {
	for (const auto& mono : scene.m_Manager.GetComponents<CMonoBehaviour>()) {
		if (const auto script{ static_cast<CMonoBehaviour*>(mono) }) {
			script->Update();
		}
	}
}