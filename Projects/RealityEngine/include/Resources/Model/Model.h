// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <string>
#include <vector>

#include "Vertex.h"

struct aiNode; struct aiScene; struct aiMesh;

namespace reality {
	struct Material {
		Vector3 Color{ Vector3::One }, SpecularStrength{ Vector3::One };
		float Shininess{ 64.f }, Opacity{}, Dissolve{};
		int Illum{};
		std::string Ambient, Diffuse, Specular, Normal, Height, Emissive, Reflection;
		std::string Name;
	};

	struct Mesh {
		uint8 Attribute{ VertexAttribute::Position };
		std::vector<Vertex> Vertices;
		std::vector<unsigned> Indices;
		Material Material;
		std::string Name;
	};

	struct ModelSettings {
		std::string Path;
	};

	struct RE_CORE Model {
		std::string Path;
		std::vector<Mesh> Meshes;

		Model() = default;
		explicit Model(ModelSettings settings);

	private:
		void StringToBinary(std::FILE* outputFile, const std::string& string);
		void BinaryToString(std::FILE* inputFile, std::string& string);
		void MaterialToBinary(std::FILE* outputFile, const Material& resource);
		Material BinaryToMaterial(std::FILE* inputFile);
		void ModelToBinary(std::FILE* outputFile);
		void BinaryToModel(std::FILE* inputFile);
		void ProcessNode(const aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(const aiMesh* node, const aiScene* scene);
		void ProcessVertices(const aiMesh* amesh, Mesh& resource);
		void ProcessIndices(const aiMesh* amesh, Mesh& resource);
		void ProcessMaterial(const aiMesh* amesh, const aiScene* scene, Material& resource);
	};
}