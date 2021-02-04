	#version 440 core

out vec4 FragColor;
in vec3 TexCoords;

layout(binding = 0) uniform samplerCube uCubeMap;

void main()
{    
	FragColor = texture(uCubeMap, TexCoords);
}