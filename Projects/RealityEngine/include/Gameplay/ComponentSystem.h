// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Rendering/Opengl/GLParticleSystem.h"
#include "Rendering/Opengl/GLPipeline.h"
#include "Rendering/Opengl/GLMaterial.h"
#include "Rendering/Opengl/GLContext.h"
#include "Rendering/Opengl/GLLight.h"
#include "Rendering/Opengl/GLMesh.h"
#include "Rendering/Opengl/GLModel.h"
#include "Component/Components.h"
#include "Windowing/IO.h"
#include "Scene.h"

namespace reality {
	class ComponentSystem {
	public:
		void UpdateTransforms(Scene& scene) const;
		void UpdateCameras(Scene& scene, Vector2 windowSize) const;
		void UpdateLights(Scene& scene) const;
		void UpdateMeshesShadow(Scene& scene) const;
		void UpdateMeshes(Scene& scene) const;
		void UpdateParticles(Scene& scene) const;
	};
}

inline void reality::ComponentSystem::UpdateTransforms(Scene& scene) const {
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

	for (const auto& object : scene.GetGameObjects()) {
		if (object->Transform.IsRoot()) {
			UpdateHierarchy(object->Transform);
		}
	}
}

inline void reality::ComponentSystem::UpdateCameras(Scene& scene, Vector2 windowSize) const {
	if (auto cameras{ scene.GetComponentManager().GetComponents<CCamera>() }) {
		for (const auto& camera : *cameras) {
			CCamera::s_Main = static_cast<CCamera*>(camera);
		}
	}
	if (CCamera::s_Main) {
		if (const auto transform{ CCamera::s_Main->GetGameObject().GetComponent<CTransform>() }) {
			GLContext::SetProjectionMatrix(Matrix4::Perspective(windowSize.X / windowSize.Y, CCamera::s_Main->Near,
				CCamera::s_Main->Far, CCamera::s_Main->Fov));
			GLContext::SetViewMatrix(Matrix4::LookAt(transform->GetPosition(), transform->GetForward(), transform->GetUp()));
		}
	}
}

inline void reality::ComponentSystem::UpdateLights(Scene& scene) const {
	if (const auto lights{ scene.GetComponentManager().GetComponents<CLight>() }) {
		auto glLights{ new GLLight[lights->size()] };
		const GLLight* directionalShadow{};
		for (auto i{ 0 }; i < lights->size(); ++i) {
			const auto& light{ *static_cast<const CLight*>((*lights)[i]) };
			glLights[i].Color = light.Color;
			glLights[i].Position = light.GetGameObject().Transform.GetPosition();
			glLights[i].Direction = light.GetGameObject().Transform.GetForward();
			glLights[i].Cutoff = light.Range - 10.f;
			glLights[i].Outcutoff = light.SpotAngle;
			glLights[i].Type = (enum GLLight::Type)light.Type;
			glLights[i].Intensity = light.Intensity;
			glLights[i].Shadow = (enum GLLight::Shadow)light.Shadow;

			if (light.Type == CLight::Type::Directional && light.Shadow == CLight::Shadow::Soft) {
				directionalShadow = &glLights[i];
			}
		}
		if (directionalShadow) {
			GLContext::SetShadowMatrix(directionalShadow->Direction, {}, { -15.f, 15.f, -15.f, 15.f, -15.f, 15.f });
		}
		GLContext::SetLights(glLights, (unsigned)lights->size());
		delete[] glLights;
	}
}

inline void reality::ComponentSystem::UpdateMeshesShadow(Scene& scene) const {
	if (const auto meshes{ scene.GetComponentManager().GetComponents<CMeshRenderer>() }) {
		for (const auto& mesh : *meshes) {
			if (mesh->GetGameObject().IsActive) {
				GLContext::SetModelMatrix(mesh->GetGameObject().Transform.GetTrs());
				if (const auto glModel{ static_cast<CMeshRenderer*>(mesh)->GetModel() }) {
					for (const auto& glmesh : glModel->Meshes) {
						glmesh->Draw();
					}
				}
			}
		}
	}
}

inline void reality::ComponentSystem::UpdateMeshes(Scene& scene) const {
	if (const auto meshes{ scene.GetComponentManager().GetComponents<CMeshRenderer>() }) {
		for (const auto& mesh : *meshes) {
			if (mesh->GetGameObject().IsActive) {
				GLContext::SetModelMatrix(mesh->GetGameObject().Transform.GetTrs());
				if (const auto glModel{ static_cast<CMeshRenderer*>(mesh)->GetModel() }) {
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
}

inline void reality::ComponentSystem::UpdateParticles(Scene& scene) const {
	if (const auto systems{ scene.GetComponentManager().GetComponents<CParticleSystem>() }) {
		for (const auto& system : *systems) {
			if (const auto glSystem{ static_cast<CParticleSystem*>(system)->System }) {
				glSystem->Direction = Vector3::Normalize(system->GetGameObject().Transform.GetForward());
				glSystem->Position = system->GetGameObject().Transform.GetPosition();
				if (auto camera{ CCamera::s_Main }) {
					glSystem->Update(g_Io->Time->GetDeltaTime() * glSystem->Speed, 
						camera->GetGameObject().Transform.GetPosition());
				}
			}
		}
	}
}