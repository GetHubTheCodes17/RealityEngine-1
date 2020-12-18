R""(	
#version 440 core

layout(location = 0) out vec3 FragColor;
layout(location = 1) out vec3 BrightColor;

uniform vec3 uColor;

void main()
{    
	FragColor = uColor;
	BrightColor = vec3(0.0, 0.0, 0.0);
}
)""