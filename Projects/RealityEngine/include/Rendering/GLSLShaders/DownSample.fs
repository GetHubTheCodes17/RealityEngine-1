R""(
#version 440 core

out vec3 FragColor;
noperspective in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uImage;

uniform vec3 uScale = vec3(0.7, 0.7, 0.7);
uniform vec3 uBias = vec3(-0.85, -0.85, -0.85);

void main() 
{
    FragColor = max(vec3(0.0), texture(uImage, TexCoords).rgb + uBias) * uScale;
}
)""