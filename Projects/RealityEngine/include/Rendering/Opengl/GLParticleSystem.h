// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <utility>

#include "Core/Maths/Vector3.h"

namespace reality {
	class RE_CORE GLParticleSystem {
	public:
		static constexpr auto s_MaxParticlesSize{ 2500u };
		static constexpr uint8 s_ParticleTransparency{ 150 };

		const class GLTexture* Texture{};
		float Speed{ 0.5f }, Spread{ 2.f }, Size{ 0.1f }, MaxLife{ 0.8f }, Gravity{ Mathf::G };
		Vector3 Position, Direction{ 0.f, 8.f, 0.f }, StartColor{ 255.f, 0.f, 0.f }, EndColor{ 0.f, 0.f, 0.f };

		GLParticleSystem();
		GLParticleSystem(GLParticleSystem&&) noexcept;
		GLParticleSystem& operator=(GLParticleSystem&&) noexcept;
		~GLParticleSystem();

		void Update(float deltaTime, Vector3 cameraPosition);

	private:
		struct Particle {
			Vector3 Position;
			float Size{};
			uint8 Color[4]{ 0, 0, 0, s_ParticleTransparency };
			Vector3 Speed;
			float Life{}, DistanceToCamera{ -1.f };
		};
		Particle* m_Particles{ new Particle[s_MaxParticlesSize] };
		int m_LastUnusedParticle{};

		struct Handle {
			unsigned Vao{}, Vbo{}, QuadVbo{};
		};
		Handle m_Handle;

		void Render() const;
		void UpdateParticles(float deltaTime, Vector3 cameraPosition);
	};
}

inline reality::GLParticleSystem::GLParticleSystem(GLParticleSystem&& other) noexcept :
	Texture{ other.Texture }, Speed{ other.Speed }, Spread{ other.Spread }, Size{ other.Size },
	MaxLife{ other.MaxLife }, Gravity{ other.Gravity }, Direction{ std::move(other.Direction) },
	StartColor{ std::move(other.StartColor) }, EndColor{ std::move(other.EndColor) },
	m_Particles{ std::exchange(other.m_Particles, nullptr) }, m_LastUnusedParticle{ other.m_LastUnusedParticle },
	m_Handle{ std::exchange(other.m_Handle, {}) }
{}

inline reality::GLParticleSystem& reality::GLParticleSystem::operator=(GLParticleSystem&& other) noexcept {
	Texture = other.Texture;
	Speed = other.Speed;
	Spread = other.Spread;
	Size = other.Size;
	MaxLife = other.MaxLife;
	Gravity = other.Gravity;
	Direction = std::move(other.Direction);
	StartColor = std::move(other.StartColor);
	EndColor = std::move(other.EndColor);
	m_Particles = std::exchange(other.m_Particles, nullptr);
	m_LastUnusedParticle = other.m_LastUnusedParticle;
	m_Handle = std::exchange(other.m_Handle, {});
	return *this;
}

inline void reality::GLParticleSystem::Update(float deltaTime, Vector3 cameraPosition) {
	UpdateParticles(deltaTime * Speed, cameraPosition);
	Render();
}