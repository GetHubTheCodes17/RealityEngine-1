// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLParticleSystem.h"

#include <glad/glad.h>

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLTexture.h"

reality::GLParticleSystem::GLParticleSystem() {
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * s_MaxParticlesSize, nullptr, GL_STREAM_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), 0);
	glVertexAttribDivisor(1, 1);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Particle), (GLvoid*)(offsetof(Particle, Color)));
	glVertexAttribDivisor(2, 1);
}

reality::GLParticleSystem::~GLParticleSystem() {
	glDeleteVertexArrays(1, &m_Handle.QuadVbo);
	glDeleteVertexArrays(1, &m_Handle.Vbo);
	glDeleteVertexArrays(1, &m_Handle.Vao);
	delete[] m_Particles;
}

void reality::GLParticleSystem::Render() const {
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
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * s_MaxParticlesSize, m_Particles);

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

void reality::GLParticleSystem::UpdateParticles(float deltaTime, Vector3 cameraPosition) {
	auto FindUnusedParticle = [this] {
		for (auto i{ m_LastUnusedParticle }; i < s_MaxParticlesSize; ++i) {
			if (m_Particles[i].Life <= 0.f) {
				return i;
			}
		}
		for (auto i{ 0 }; i < m_LastUnusedParticle; ++i) {
			if (m_Particles[i].Life <= 0.f) {
				return i;
			}
		}
		return 0;
	};

	const auto newParticlesCount{ deltaTime > 0.016f ? 16 : (int)(deltaTime * 1000.f) };
	for (auto i{ 0 }; i < newParticlesCount; ++i) {
		m_LastUnusedParticle = FindUnusedParticle();
		m_Particles[m_LastUnusedParticle].Life = MaxLife;
		m_Particles[m_LastUnusedParticle].Size = Size;
		m_Particles[m_LastUnusedParticle].Speed.X = Direction.X + (float(std::rand() % 20) - 10.f) / 10.f * Spread;
		m_Particles[m_LastUnusedParticle].Speed.Y = Direction.Y + (float(std::rand() % 20) - 10.f) / 10.f * Spread;
		m_Particles[m_LastUnusedParticle].Speed.Z = Direction.Z + (float(std::rand() % 20) - 10.f) / 10.f * Spread;
		m_Particles[m_LastUnusedParticle].Position.X = Position.X;
		m_Particles[m_LastUnusedParticle].Position.Y = Position.Y;
		m_Particles[m_LastUnusedParticle].Position.Z = Position.Z;
		m_Particles[m_LastUnusedParticle].DistanceToCamera = Vector3::SqrDistance(
			m_Particles[m_LastUnusedParticle].Position, cameraPosition);
	}

	for (auto i{ 0 }; i < s_MaxParticlesSize; ++i) {
		m_Particles[i].Life -= deltaTime;
		if (m_Particles[i].Life > 0.f) {
			m_Particles[i].Speed.Y -= Gravity * deltaTime;
			m_Particles[i].Position.X += m_Particles[i].Speed.X * deltaTime;
			m_Particles[i].Position.Y += m_Particles[i].Speed.Y * deltaTime;
			m_Particles[i].Position.Z += m_Particles[i].Speed.Z * deltaTime;
			const auto t{ (MaxLife - m_Particles[i].Life) / MaxLife };
			m_Particles[i].Color[0] = (uint8)(StartColor.X + (EndColor.X - StartColor.X) * t);
			m_Particles[i].Color[1] = (uint8)(StartColor.Y + (EndColor.Y - StartColor.Y) * t);
			m_Particles[i].Color[2] = (uint8)(StartColor.Z + (EndColor.Z - StartColor.Z) * t);
			m_Particles[i].DistanceToCamera = Vector3::SqrDistance(m_Particles[i].Position, cameraPosition);
		}
		else {
			m_Particles[i].Position.X = std::numeric_limits<float>::max();
		}
	}

	/*std::sort(m_Particles, m_Particles + s_MaxParticlesSize,
		[](const auto& lhs, const auto& rhs) { return lhs.DistanceToCamera > rhs.DistanceToCamera; }
	);*/
}