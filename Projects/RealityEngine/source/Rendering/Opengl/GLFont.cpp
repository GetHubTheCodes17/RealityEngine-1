// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLFont.h"

#include <glad/glad.h>

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Core/Maths/Matrix4.h"

reality::GLFont::GLFont(GLFontSettings settings) {
	glGenVertexArrays(1, &m_Handle.Vao);
	glBindVertexArray(m_Handle.Vao);
	glGenBuffers(1, &m_Handle.Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, nullptr);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c{}; c < settings.Characters.size(); ++c) {
		m_Handle.Characters[c] = { GLTexture{ { settings.Characters[c].Buffer, (int)settings.Characters[c].Size.X,
			(int)settings.Characters[c].Size.Y, false, GLTextureFormat::Red, GLTextureFormat::Red,
			GLTextureInternalType::Ubyte, GLTextureType::Texture2D, GLTextureWrapping::ClampToEdge,
			GLTextureFiltering::Linear } }, settings.Characters[c].Size, settings.Characters[c].Bearing,
			settings.Characters[c].Advance };
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

void reality::GLFont::Draw(std::string_view text, const Viewport& viewport, Vector2 windowSize) const {
	GLint previousShaderProgram{};
	glGetIntegerv(GL_CURRENT_PROGRAM, &previousShaderProgram);
	GLboolean previousBlendState{};
	glGetBooleanv(GL_BLEND, &previousBlendState);
	GLboolean previousBlendSrc{};
	glGetBooleanv(GL_BLEND_SRC_ALPHA, &previousBlendSrc);
	GLboolean previousBlendDst{};
	glGetBooleanv(GL_BLEND_DST_ALPHA, &previousBlendDst);

	if (!previousBlendState) {
		glEnable(GL_BLEND);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(m_Handle.Vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle.Vbo);

	g_ShaderHelper->Text.Bind();
	g_ShaderHelper->Text.Set(1, Matrix4::Ortho({ 0.f, windowSize.X, windowSize.Y, 0.f, -1.f, 1.f }));
	g_ShaderHelper->Text.Set(3, Color);

	auto x{ viewport.X * windowSize.X };
	const auto y{ viewport.Y * windowSize.Y };

	for (const auto& c : text) {
		const auto& character{ m_Handle.Characters[(std::size_t)(c)] };
		const auto xPos{ x + character.Bearing.X * viewport.Width };
		const auto yPos{ y + (m_Handle.Characters['X'].Bearing.Y - character.Bearing.Y) * viewport.Height };
		const auto width{ character.Size.X * viewport.Width };
		const auto height{ character.Size.Y * viewport.Height };
		x += (character.Advance >> 6) * viewport.Width;

		const std::array vertices{ std::array{ xPos, yPos + height, 0.f, 1.f }, std::array{ xPos + width, yPos, 1.f, 0.f }, 
			std::array{ xPos, yPos, 0.f, 0.f }, std::array{ xPos, yPos + height, 0.f, 1.f },
			std::array{ xPos + width, yPos + height, 1.f, 1.f }, std::array{ xPos + width, yPos, 1.f, 0.f } };

		character.Texture.Bind(0);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices.data());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	if (!previousBlendState) {
		glDisable(GL_BLEND);
	}
	glBlendFunc(previousBlendSrc, previousBlendDst);
	glUseProgram((GLuint)previousShaderProgram);
}