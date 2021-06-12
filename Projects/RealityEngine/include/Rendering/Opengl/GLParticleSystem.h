// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>
#include <vector>

#include "Core/Platform.h"
#include "Core/Maths/Mathf.h"
#include "Core/Maths/Vector3.h"

namespace Reality {
	struct GLParticle {
		static constexpr uint8 s_ParticleTransparency{ 150 };

		Vector3 Position;
		float Size{};
		uint8 Color[4]{ 0, 0, 0, s_ParticleTransparency };
		Vector3 Speed;
		float Life{}, DistanceToCamera{ -1.f };
	};

	class RE_CORE GLParticleSystem {
	public:
		static constexpr auto s_MaxParticlesSize{ 1000u };

		const class GLTexture* Texture{};
		float Speed{ 0.5f }, Spread{ 2.f }, Size{ 0.1f }, MaxLife{ 0.8f }, Gravity{ Mathf::G };
		Vector3 Position, Direction{ 0.f, 8.f, 0.f }, StartColor{ 255.f, 0.f, 0.f }, EndColor{ 0.f, 0.f, 0.f };

		GLParticleSystem();
		GLParticleSystem(GLParticleSystem&&) noexcept;
		GLParticleSystem& operator=(GLParticleSystem&&) noexcept;
		~GLParticleSystem();

		void Update(float deltaTime, Vector3 cameraPosition);

	private:
		std::vector<GLParticle> m_Particles;
		unsigned m_LastUnusedParticle{};

		struct Handle {
			unsigned Vao{}, Vbo{}, QuadVbo{};
		};
		Handle m_Handle;

		void Render() const;
		void UpdateParticles(float deltaTime, Vector3 cameraPosition);
	};
}

inline Reality::GLParticleSystem::GLParticleSystem(GLParticleSystem&& other) noexcept :
	Texture{ other.Texture }, Speed{ other.Speed }, Spread{ other.Spread }, Size{ other.Size },
	MaxLife{ other.MaxLife }, Gravity{ other.Gravity }, Direction{ std::move(other.Direction) },
	StartColor{ std::move(other.StartColor) }, EndColor{ std::move(other.EndColor) },
	m_Particles{ std::move(other.m_Particles) }, m_LastUnusedParticle{ other.m_LastUnusedParticle },
	m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline Reality::GLParticleSystem& Reality::GLParticleSystem::operator=(GLParticleSystem&& other) noexcept {
	Texture = other.Texture;
	Speed = other.Speed;
	Spread = other.Spread;
	Size = other.Size;
	MaxLife = other.MaxLife;
	Gravity = other.Gravity;
	Direction = std::move(other.Direction);
	StartColor = std::move(other.StartColor);
	EndColor = std::move(other.EndColor);
	m_Particles = std::move(other.m_Particles);
	m_LastUnusedParticle = other.m_LastUnusedParticle;
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline void Reality::GLParticleSystem::Update(float deltaTime, Vector3 cameraPosition) {
	UpdateParticles(deltaTime * Speed, cameraPosition);
	Render();
}