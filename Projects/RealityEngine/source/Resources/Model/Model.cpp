// Copyright Reality Engine. All Rights Reserved.

#define _CRT_SECURE_NO_WARNINGS

#include "Resources/Model/Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/Tools/Logger.h"

reality::Model::Model(ModelSettings settings) : 
	Path{ g_ResourcesPath + settings.Path } 
{
	const auto path{ Path.substr(0, Path.find_last_of('/')) };
	const auto binaryPath{ path + path.substr(std::strlen(g_ResourcesPath) + sizeof("Models") - 1) + g_ResourcesExtension };

	if (auto inputFile{ std::fopen(binaryPath.c_str(), "rb") }) {
		BinaryToModel(inputFile);
		std::fclose(inputFile);
	}
	else {
		Assimp::Importer importer;
		const auto scene{ importer.ReadFile(Path,
			aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_GenSmoothNormals |
			aiProcess_GenBoundingBoxes | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph) };
		Path = settings.Path.substr(0, settings.Path.find_last_of('/')).c_str();

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			RE_LOG_WARNING("Error with Assimp : %s", importer.GetErrorString());
			return;
		}
		ProcessNode(scene->mRootNode, scene);

		auto outputFile{ std::fopen(binaryPath.c_str(), "wb") };
		ModelToBinary(outputFile);
		std::fclose(outputFile);
	}
}

bool reality::Model::IsExtensionSupported(std::string_view extension) {
	return Assimp::Importer().IsExtensionSupported(extension.data());
}

void reality::Model::StringToBinary(std::FILE* outputFile, const std::string& string) {
	const auto size{ (unsigned)string.size() };
	std::fwrite(&size, sizeof(unsigned), 1, outputFile);

	if (string.empty()) {
		return;
	}
	std::fwrite(string.c_str(), sizeof(char), string.size(), outputFile);
}

void reality::Model::BinaryToString(std::FILE* inputFile, std::string& string) {
	auto size{ 0u };
	std::fread(&size, sizeof(unsigned), 1, inputFile);

	string.resize(size);
	for (auto& c : string) {
		std::fread(&c, sizeof(char), 1, inputFile);
	}
}

void reality::Model::MaterialToBinary(std::FILE* outputFile, const Material& resource) {
	std::fwrite(&resource, offsetof(Material, Ambient), 1, outputFile);
	StringToBinary(outputFile, resource.Ambient);
	StringToBinary(outputFile, resource.Diffuse);
	StringToBinary(outputFile, resource.Specular);
	StringToBinary(outputFile, resource.Normal);
	StringToBinary(outputFile, resource.Height);
	StringToBinary(outputFile, resource.Emissive);
	StringToBinary(outputFile, resource.Reflection);
	StringToBinary(outputFile, resource.Name);
}

reality::Material reality::Model::BinaryToMaterial(std::FILE* inputFile) {
	Material material;
	std::fread(&material, offsetof(Material, Ambient), 1, inputFile);
	BinaryToString(inputFile, material.Ambient);
	BinaryToString(inputFile, material.Diffuse);
	BinaryToString(inputFile, material.Specular);
	BinaryToString(inputFile, material.Normal);
	BinaryToString(inputFile, material.Height);
	BinaryToString(inputFile, material.Emissive);
	BinaryToString(inputFile, material.Reflection);
	BinaryToString(inputFile, material.Name);
	return material;
}

void reality::Model::ModelToBinary(std::FILE* outputFile) {
	const auto meshesSize{ (unsigned)Meshes.size() };
	std::fwrite(&meshesSize, sizeof(unsigned), 1, outputFile);

	for (const auto& mesh : Meshes) {
		StringToBinary(outputFile, mesh.Name);

		std::fwrite(&mesh.Attribute, sizeof(uint8), 1, outputFile);

		const auto verticesSize{ (unsigned)mesh.Vertices.size() };
		std::fwrite(&verticesSize, sizeof(unsigned), 1, outputFile);

		if (verticesSize) {
			std::fwrite(mesh.Vertices.data(), sizeof(Vertex), (std::size_t)verticesSize, outputFile);
		}

		const auto indicesSize{ (unsigned)mesh.Indices.size() };
		std::fwrite(&indicesSize, sizeof(unsigned), 1, outputFile);

		if (indicesSize) {
			std::fwrite(mesh.Indices.data(), sizeof(unsigned), (std::size_t)indicesSize, outputFile);
		}
		std::fwrite(&mesh.Aabb, sizeof(AABB), 1, outputFile);

		MaterialToBinary(outputFile, mesh.Material);
	}
}

void reality::Model::BinaryToModel(std::FILE* inputFile) {
	auto meshesSize{ 0u }, verticesSize{ 0u }, indicesSize{ 0u };
	std::fread(&meshesSize, sizeof(unsigned), 1, inputFile);
	Meshes.resize(meshesSize);

	for (auto& mesh : Meshes) {
		BinaryToString(inputFile, mesh.Name);

		std::fread(&mesh.Attribute, sizeof(uint8), 1, inputFile);

		std::fread(&verticesSize, sizeof(unsigned), 1, inputFile);
		if (verticesSize) {
			mesh.Vertices.resize(verticesSize);
			std::fread(mesh.Vertices.data(), sizeof(Vertex), (std::size_t)verticesSize, inputFile);
		}

		std::fread(&indicesSize, sizeof(unsigned), 1, inputFile);
		if (indicesSize) {
			mesh.Indices.resize(indicesSize);
			std::fread(mesh.Indices.data(), sizeof(unsigned), (std::size_t)indicesSize, inputFile);
		}
		std::fread(&mesh.Aabb, sizeof(AABB), 1, inputFile);

		mesh.Material = BinaryToMaterial(inputFile);
	}
}

void reality::Model::ProcessNode(const aiNode* node, const aiScene* scene) {
	Meshes.reserve(node->mNumMeshes);
	for (auto i{ 0u }; i < node->mNumMeshes; ++i) {
		auto mesh{ scene->mMeshes[node->mMeshes[i]] };
		Meshes.emplace_back(ProcessMesh(mesh, scene));
	}

	for (auto i{ 0u }; i < node->mNumChildren; ++i) {
		ProcessNode(node->mChildren[i], scene);
	}
}

reality::Mesh reality::Model::ProcessMesh(const aiMesh* amesh, const aiScene* scene) {
	Mesh mesh;
	mesh.Name = amesh->mName.C_Str();
	ProcessVertices(amesh, mesh);
	ProcessIndices(amesh, mesh);

	if (amesh->mMaterialIndex) {
		ProcessMaterial(amesh, scene, mesh.Material);
		mesh.Aabb = { { amesh->mAABB.mMin.x, amesh->mAABB.mMin.y, amesh->mAABB.mMin.z },
			{ amesh->mAABB.mMax.x, amesh->mAABB.mMax.y, amesh->mAABB.mMax.z } };
	}
	return mesh;
}

void reality::Model::ProcessVertices(const aiMesh* amesh, Mesh& resource) {
	resource.Attribute |= amesh->HasNormals() ? VertexAttribute::Normal : 0;
	resource.Attribute |= amesh->HasTextureCoords(0) ? VertexAttribute::Uv : 0;
	resource.Attribute |= amesh->HasTangentsAndBitangents() ? VertexAttribute::Tangents : 0;

	resource.Vertices.reserve(amesh->mNumVertices);
	Vertex vertex;
	for (auto i{ 0u }; i < amesh->mNumVertices; ++i) {
		vertex.Position.X = amesh->mVertices[i].x;
		vertex.Position.Y = amesh->mVertices[i].y;
		vertex.Position.Z = amesh->mVertices[i].z;

		if (amesh->HasNormals()) {
			vertex.Normal.X = amesh->mNormals[i].x;
			vertex.Normal.Y = amesh->mNormals[i].y;
			vertex.Normal.Z = amesh->mNormals[i].z;
		}
		if (amesh->HasTextureCoords(0)) {
			vertex.Uv.X = amesh->mTextureCoords[0][i].x;
			vertex.Uv.Y = amesh->mTextureCoords[0][i].y;
		}
		if (amesh->HasTangentsAndBitangents()) {
			vertex.Tangent.X = amesh->mTangents[i].x;
			vertex.Tangent.Y = amesh->mTangents[i].y;
			vertex.Tangent.Z = amesh->mTangents[i].z;
			vertex.Bitangent.X = amesh->mBitangents[i].x;
			vertex.Bitangent.Y = amesh->mBitangents[i].y;
			vertex.Bitangent.Z = amesh->mBitangents[i].z;
		}
		resource.Vertices.emplace_back(vertex);
	}
}

void reality::Model::ProcessIndices(const aiMesh* amesh, Mesh& resource) {
	for (auto i{ 0u }; i < amesh->mNumFaces; ++i) {
		const auto& face{ amesh->mFaces[i] };
		for (auto j{ 0u }; j < face.mNumIndices; ++j) {
			resource.Indices.emplace_back(face.mIndices[j]);
		}
	}
}

void reality::Model::ProcessMaterial(const aiMesh* amesh, const aiScene* scene, Material& resource) {
	const auto mat{ scene->mMaterials[amesh->mMaterialIndex] };
	mat->Get(AI_MATKEY_SHININESS, resource.Shininess);
	mat->Get(AI_MATKEY_OPACITY, resource.Opacity);

	aiColor4D diffuse;
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
	std::memcpy(&resource.Color, &diffuse, sizeof(Vector3));

	aiColor4D specular;
	aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &specular);
	std::memcpy(&resource.SpecularStrength, &specular, sizeof(Vector3));

	aiString name;
	aiGetMaterialString(mat, AI_MATKEY_NAME, &name);
	resource.Name = name.C_Str() + std::string{ "mat" };

	aiString texturePath;
	if (mat->GetTextureCount(aiTextureType_DIFFUSE)) {
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);
		resource.Diffuse = Path + '/' + texturePath.C_Str();
	}
	if (mat->GetTextureCount(aiTextureType_SPECULAR)) {
		mat->GetTexture(aiTextureType_SPECULAR, 0, &texturePath);
		resource.Specular = Path + '/' + texturePath.C_Str();
	}
	if (mat->GetTextureCount(aiTextureType_NORMALS)) {
		mat->GetTexture(aiTextureType_NORMALS, 0, &texturePath);
		resource.Normal = Path + '/' + texturePath.C_Str();
	}
	if (mat->GetTextureCount(aiTextureType_HEIGHT)) {
		mat->GetTexture(aiTextureType_HEIGHT, 0, &texturePath);
		resource.Height = Path + '/' + texturePath.C_Str();
	}
	if (mat->GetTextureCount(aiTextureType_EMISSIVE)) {
		mat->GetTexture(aiTextureType_EMISSIVE, 0, &texturePath);
		resource.Emissive = Path + '/' + texturePath.C_Str();
	}

	// TODO : Store the reflection texture in the ambient texture because aiTextureType_REFLECTION is not working
	if (mat->GetTextureCount(aiTextureType_AMBIENT)) {
		mat->GetTexture(aiTextureType_AMBIENT, 0, &texturePath);
		resource.Reflection = Path + '/' + texturePath.C_Str();
	}
}