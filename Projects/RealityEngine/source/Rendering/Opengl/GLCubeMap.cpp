// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLCubeMap.h"

#include <glad/glad.h>

Reality::GLCubeMap::GLCubeMap(GLCubeMapSettings settings) {
	glGenTextures(1, &m_Handle.Id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Handle.Id);

	for (GLuint i{}; i < settings.Textures.size(); ++i) {
		constexpr GLenum formats[]{ GL_RED, GL_RGB, GL_SRGB, GL_RGBA, GL_RGB16F };
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, settings.Textures[i].Width, settings.Textures[i].Height, 
			0, formats[(int)settings.Textures[i].Format], GL_UNSIGNED_BYTE, settings.Textures[i].Image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Reality::GLCubeMap::~GLCubeMap() {
	glDeleteTextures(1, &m_Handle.Id);
}

void Reality::GLCubeMap::Bind(unsigned index) const {
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Handle.Id);
}