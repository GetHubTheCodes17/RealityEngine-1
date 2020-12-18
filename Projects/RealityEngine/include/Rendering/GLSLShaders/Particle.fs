R""(
#version 440 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec3 BrightColor;

in vec4 Color;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uTexture;

void main()
{
	FragColor = texture(uTexture, TexCoords) * Color;
	BrightColor = vec3(0.0, 0.0, 0.0);
}
)""