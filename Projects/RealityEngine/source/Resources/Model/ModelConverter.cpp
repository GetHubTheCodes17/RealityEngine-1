// Copyright Reality Engine. All Rights Reserved.

#include "Resources/ResourceLocator.h"

reality::GLModel reality::loader::ConvertModel(GLMeshSettings& properties, const Model& resource) {
	auto CreateMesh = [](auto& properties, const auto& mesh) {
		auto CreateMaterial = [](const auto& material) {
			auto CreateTexture = [](const auto& path) {
				return path.empty() ? nullptr :
					&g_TextureManager->Load(path.substr(path.find_last_of("/") + 1).c_str(), { path });
			};

			auto& materialGpu{ g_MaterialManager->emplace(material.Name, GLMaterial{}).first->second };
			materialGpu.Color = material.Color;
			materialGpu.SpecularStrength = material.SpecularStrength;
			materialGpu.Shininess = material.Shininess;
			materialGpu.Albedo = CreateTexture(material.Diffuse);
			materialGpu.Specular = CreateTexture(material.Specular);
			materialGpu.Normal = CreateTexture(material.Normal);
			materialGpu.Height = CreateTexture(material.Height);
			materialGpu.Reflection = CreateTexture(material.Reflection);
			materialGpu.Emissive = CreateTexture(material.Emissive);
			return &materialGpu;
		};

		properties.Vertices = reinterpret_cast<const float*>(mesh.Vertices.data());
		properties.VerticesSize = (unsigned)(mesh.Vertices.size());
		properties.Indices = mesh.Indices.data();
		properties.IndicesSize = (unsigned)(mesh.Indices.size());
		properties.Attribute = mesh.Attribute;
		auto& meshGpu{ g_MeshManager->emplace(mesh.Name, properties).first->second };
		meshGpu.Material = CreateMaterial(mesh.Material);
		return &meshGpu;
	};

	GLModel model;
	for (const auto& mesh : resource.Meshes) {
		model.Meshes.emplace_back(CreateMesh(properties, mesh));
	}
	return model;
}