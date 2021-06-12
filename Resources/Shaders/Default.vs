// Copyright Reality Engine. All Rights Reserved.

#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

layout (binding = 0, std140) uniform Matrices
{
	mat4 uView;
	mat4 uProjection;
};

uniform mat4 uModel;
uniform vec3 uViewPos;

out VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 ViewPos;
	vec3 ViewDir;
	mat3 Tbn;
} vs_out;

void main()
{
	vec4 worldSpaceCoords = uModel * vec4(position, 1.0);
	vec4 clipSpaceCoords = uProjection * uView * uModel * vec4(position, 1.0);
	mat3 normalMatrix = transpose(inverse(mat3(uModel)));

	vec3 t = normalize(normalMatrix * tangent);
	vec3 b = normalize(normalMatrix * bitangent);
	vec3 n = normalize(normalMatrix * normal);
	t = normalize(t - dot(t, n) * n);

	vs_out.Tbn = mat3(t, b, n);
	vs_out.FragPos = vec3(worldSpaceCoords);
	vs_out.Normal = n;
	vs_out.TexCoords = uv;
	vs_out.ViewPos = uViewPos;
	vs_out.ViewDir = normalize(vs_out.ViewPos - vs_out.FragPos);

	gl_Position = clipSpaceCoords;
}
