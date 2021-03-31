// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <cereal/cereal.hpp>

#include "Rendering/Opengl/GLMaterial.h"
#include "Rendering/Opengl/GLTexture.h"
#include "Rendering/Opengl/GLModel.h"
#include "Rendering/Opengl/GLMesh.h"
#include "Rendering/Opengl/GLShader.h"
#include "Rendering/Opengl/GLCubeMap.h"
#include "Rendering/Opengl/GLFont.h"
#include "Resources/Model/Model.h"
#include "Resources/Shader/Shader.h"
#include "Resources/Texture/Texture.h"
#include "Resources/Skybox/Skybox.h"

namespace Reality {
	template <class Archive>
	void serialize(Archive& archive, ModelSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, ShaderSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, SkyboxSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, TextureSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, FontSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, GLMeshSettings& settings);
	template <class Archive>
	void serialize(Archive&, GLShaderSettings&);
	template <class Archive>
	void serialize(Archive&, GLCubeMapSettings&);
	template <class Archive>
	void serialize(Archive& archive, GLTextureSettings& settings);
	template <class Archive>
	void serialize(Archive& archive, GLFontSettings& settings);
}

template <class Archive>
void Reality::serialize(Archive& archive, ModelSettings& settings) {
	archive(cereal::make_nvp("Path", settings.Path));
}

template <class Archive>
void Reality::serialize(Archive& archive, ShaderSettings& settings) {
	archive(cereal::make_nvp("VertexPath", settings.VertexPath),
		cereal::make_nvp("FragmentPath", settings.FragmentPath),
		cereal::make_nvp("GeometryPath", settings.GeometryPath));
}

template <class Archive>
void Reality::serialize(Archive& archive, SkyboxSettings& settings) {
	archive(cereal::make_nvp("Left", settings.Left.Path),
		cereal::make_nvp("Right", settings.Right.Path),
		cereal::make_nvp("Up", settings.Up.Path),
		cereal::make_nvp("Down", settings.Down.Path),
		cereal::make_nvp("Front", settings.Front.Path),
		cereal::make_nvp("Back", settings.Back.Path));
}

template <class Archive>
void Reality::serialize(Archive& archive, TextureSettings& settings) {
	archive(cereal::make_nvp("Path", settings.Path));
}

template <class Archive>
void Reality::serialize(Archive& archive, FontSettings& settings) {
	archive(cereal::make_nvp("Path", settings.Path),
		cereal::make_nvp("PixelSize", settings.PixelSize));
}

template <class Archive>
void Reality::serialize(Archive& archive, GLMeshSettings& settings) {
	archive(cereal::make_nvp("Usage", settings.Usage),
		cereal::make_nvp("DrawType", settings.DrawType),
		cereal::make_nvp("Attribute", settings.Attribute));
}

template <class Archive>
void Reality::serialize(Archive&, GLShaderSettings&) {
}

template <class Archive>
void Reality::serialize(Archive&, GLCubeMapSettings&) {
}

template <class Archive>
void Reality::serialize(Archive& archive, GLTextureSettings& settings) {
	archive(cereal::make_nvp("HasMipmap", settings.HasMipmap),
		cereal::make_nvp("InternalFormat", settings.InternalFormat),
		cereal::make_nvp("Format", settings.Format),
		cereal::make_nvp("InternalType", settings.InternalType),
		cereal::make_nvp("Type", settings.Type),
		cereal::make_nvp("Wrap", settings.Wrap),
		cereal::make_nvp("Filter", settings.Filter),
		cereal::make_nvp("Samples", settings.Samples));
}

template<class Archive>
void Reality::serialize(Archive&, GLFontSettings&) {
}