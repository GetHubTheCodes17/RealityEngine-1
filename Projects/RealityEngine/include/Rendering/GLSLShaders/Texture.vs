R""( 
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 uv;

out vec2 TexCoords;

void main()
{
	TexCoords = uv;

	// Multiply by 2 because the Quad we are using is 0.5 by 0.5 size instead of 1 by 1
	gl_Position = vec4(position * 2.0, 1.0);
}
)""