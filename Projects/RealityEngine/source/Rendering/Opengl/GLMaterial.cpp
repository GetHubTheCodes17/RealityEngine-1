// Copyright Reality Engine. All Rights Reserved.

#include "Rendering/Opengl/GLMaterial.h"

#include "Rendering/Opengl/GLShaderHelper.h"
#include "Rendering/Opengl/GLTexture.h"

void Reality::GLMaterial::Bind() const {
	uint8 Mask{};

	if (Albedo) {
		Mask |= GLTextureMask::AlbedoMap;
		Albedo->Bind(0);
	}
	if (Specular) {
		Mask |= GLTextureMask::SpecularMap;
		Specular->Bind(1);
	}
	if (Normal) {
		Mask |= GLTextureMask::NormalMap;
		Normal->Bind(2);
	}
	if (Height) {
		Mask |= GLTextureMask::HeightMap;
		Height->Bind(3);
	}
	if (Reflection) {
		Mask |= GLTextureMask::ReflectionMap;
		Reflection->Bind(4);
	}
	if (Emissive) {
		Mask |= GLTextureMask::EmissiveMap;
		Emissive->Bind(5);
	}

	const auto& shader{ g_ShaderHelper->Default };
	shader.Set(2, (int)Mask);
	shader.Set(3, Color);
	shader.Set(4, SpecularStrength);
	shader.Set(5, Shininess);
}