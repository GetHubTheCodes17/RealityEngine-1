// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include "Model/ModelConverter.h"

namespace reality::loader {
	template <class Resource, class Properties, class TmpResource>
	inline Resource Convert(Properties&, const TmpResource&) = delete;
	template <>
	RE_CORE inline GLTexture Convert(GLTextureSettings& properties, const Texture& resource);
	template <>
	RE_CORE inline GLCubeMap Convert(GLCubeMapSettings& properties, const Skybox& resource);
	template <>
	RE_CORE inline GLShader Convert(GLShaderSettings& properties, const Shader& resource);
	template <>
	RE_CORE inline GLModel Convert(GLMeshSettings& properties, const Model& resource);
	template <>
	RE_CORE inline GLFont Convert(GLFontSettings& properties, const Font& resource);
}

template<>
reality::GLTexture reality::loader::Convert(GLTextureSettings& properties, const Texture& resource) {
	properties.Image = resource.Image.get();
	properties.Width = resource.Width;
	properties.Height = resource.Height;

	if (resource.Channels == 4) {
		properties.InternalFormat = properties.Format = GLTextureFormat::Rgba;
	}
	else if (resource.Channels == 1) {
		properties.InternalFormat = properties.Format = GLTextureFormat::Red;
	}
	return GLTexture{ properties };
}

template<>
reality::GLCubeMap reality::loader::Convert(GLCubeMapSettings& properties, const Skybox& resource) {
	for (std::size_t i{}; i < properties.Textures.size(); ++i) {
		properties.Textures[i].Image = resource.Textures[i].Image.get();
		properties.Textures[i].Width = resource.Textures[i].Width;
		properties.Textures[i].Height = resource.Textures[i].Height;
	}
	return GLCubeMap{ properties };
}

template<>
reality::GLShader reality::loader::Convert(GLShaderSettings& properties, const Shader& resource) {
	properties.VertexSource = resource.VertexSource;
	properties.FragmentSource = !resource.FragmentSource.empty() ? resource.FragmentSource : "";
	properties.GeometrySource = !resource.GeometrySource.empty() ? resource.GeometrySource : "";
	return GLShader{ properties };
}

template<>
reality::GLModel reality::loader::Convert(GLMeshSettings& properties, const Model& resource) {
	return ConvertModel(properties, resource);
}

template<>
reality::GLFont reality::loader::Convert(GLFontSettings& properties, const Font& resource) {
	for (std::size_t i{}; i < resource.Characters.size(); ++i) {
		properties.Characters[i].Size = resource.Characters[i].Size;
		properties.Characters[i].Bearing = resource.Characters[i].Bearing;
		properties.Characters[i].Advance = resource.Characters[i].Advance;
		properties.Characters[i].Buffer = resource.Characters[i].Buffer.get();
	}
	return GLFont{ properties };
}