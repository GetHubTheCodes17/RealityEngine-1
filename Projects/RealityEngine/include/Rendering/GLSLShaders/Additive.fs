R""( 
#version 440 core

out vec3 FragColor;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uLeft;
layout(binding = 1) uniform sampler2D uRight;

void main()
{
	FragColor = texture(uLeft, TexCoords).rgb + texture(uRight, TexCoords).rgb;
}
)""