R""(
#version 440 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec3 BrightColor;

in vec2 TexCoords;

layout(location = 3) uniform vec4 uColor;
layout(location = 4) uniform sampler2D uText;

void main()
{    
    FragColor = uColor * vec4(1.0, 1.0, 1.0, texture(uText, TexCoords).r);
    BrightColor = vec3(0.0, 0.0, 0.0);
}  
)""