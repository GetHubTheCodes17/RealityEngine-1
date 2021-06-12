// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLParticleSystem.h"

#include <glad/glad.h>
#include <algorithm>

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLTexture.h"
#include "Core/Tools/Randomizer.h"

Reality::GLParticleSystem::GLParticleSystem() :
	m_Particles(s_MaxParticlesSize)
{
	constexpr GLfloat quadPositions[]{ -0.5f,-0.5f,0.f,0.5f,-0.5f,0.f,-0.5f,0.5f,0.f,0.5f,0.5f,0.f };
	glGenVertexArrays(1, &m_Handle.Vao);
	glBindVertexArray(m_Handle.Vao);

	glGenBuffers(1, &m_Handle.QuadVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.QuadVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof quadPositions, quadPositions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glGenBuffers(1, &m_Handle.Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLParticle) * s_MaxParticlesSize, nullptr, GL_STREAM_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GLParticle), 0);
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLParticle), (GLvoid*)(offsetof(GLParticle, Color)));
	glVertexAttribDivisor(2, 1);
}

Reality::GLParticleSystem::~GLParticleSystem() {
	glDeleteVertexArrays(1, &m_Handle.QuadVbo);
	glDeleteVertexArrays(1, &m_Handle.Vbo);
	glDeleteVertexArrays(1, &m_Handle.Vao);
}

void Reality::GLParticleSystem::Render() const {
	GLint previousShaderProgram{};
	glGetIntegerv(GL_CURRENT_PROGRAM, &previousShaderProgram);
	GLboolean previousBlendState{};
	glGetBooleanv(GL_BLEND, &previousBlendState);
	GLboolean previousBlendSrc{};
	glGetBooleanv(GL_BLEND_SRC_ALPHA, &previousBlendSrc);
	GLboolean previousBlendDst{};
	glGetBooleanv(GL_BLEND_DST_ALPHA, &previousBlendDst);

	glBindVertexArray(m_Handle.Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.Vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLParticle) * s_MaxParticlesSize, m_Particles.data());

	if (!previousBlendState) {
		glEnable(GL_BLEND);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	g_ShaderHelper->Particle.Bind();
	if (Texture) {
		Texture->Bind(0);
	}
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, (GLsizei)s_MaxParticlesSize);

	if (!previousBlendState) {
		glDisable(GL_BLEND);
	}
	glBlendFunc(previousBlendSrc, previousBlendDst);
	glUseProgram((GLuint)previousShaderProgram);
}

void Reality::GLParticleSystem::UpdateParticles(float deltaTime, Vector3 cameraPosition) {
	auto FindUnusedParticleIndex = [this] {
		for (auto i{ m_LastUnusedParticle }; i < s_MaxParticlesSize; ++i) {
			if (m_Particles[i].Life <= 0.f) {
				return i;
			}
		}
		for (auto i{ 0u }; i < m_LastUnusedParticle; ++i) {
			if (m_Particles[i].Life <= 0.f) {
				return i;
			}
		}
		return 0u;
	};

	const auto newParticlesCount{ deltaTime > 0.016f ? 16 : (int)(deltaTime * 1000.f) };
	for (auto i{ 0 }; i < newParticlesCount; ++i) {
		m_LastUnusedParticle = FindUnusedParticleIndex();
		const Vector3 randDir{ g_Randomizer->GetReal(-1.f, 1.f), g_Randomizer->GetReal(-1.f, 1.f), g_Randomizer->GetReal(-1.f, 1.f) };
		m_Particles[m_LastUnusedParticle].Speed = Direction + randDir * Spread;
		m_Particles[m_LastUnusedParticle].Position = Position;
		m_Particles[m_LastUnusedParticle].DistanceToCamera = Vector3::SqrDistance(m_Particles[m_LastUnusedParticle].Position, cameraPosition);
		m_Particles[m_LastUnusedParticle].Size = Size;
		m_Particles[m_LastUnusedParticle].Life = MaxLife;
	}

	for (auto& particle : m_Particles) {
		particle.Life -= deltaTime;
		if (particle.Life > 0.f) {
			particle.Speed.Y -= Gravity * deltaTime;
			particle.Position += particle.Speed * deltaTime;

			const auto t{ (MaxLife - particle.Life) / MaxLife };
			particle.Color[0] = uint8(StartColor.X + (EndColor.X - StartColor.X) * t);
			particle.Color[1] = uint8(StartColor.Y + (EndColor.Y - StartColor.Y) * t);
			particle.Color[2] = uint8(StartColor.Z + (EndColor.Z - StartColor.Z) * t);
			particle.DistanceToCamera = Vector3::SqrDistance(particle.Position, cameraPosition);
		}
		else {
			particle.Position.X = std::numeric_limits<float>::max();
		}
	}

	/*std::ranges::sort(m_Particles, 
		[](const auto& lhs, const auto& rhs) { 
			return lhs.DistanceToCamera > rhs.DistanceToCamera; 
		}
	);*/
}