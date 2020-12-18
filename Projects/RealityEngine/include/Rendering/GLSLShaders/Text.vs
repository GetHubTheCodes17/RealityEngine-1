R""(
#version 440 core

layout(location = 0) in vec4 vertex;

out vec2 TexCoords;

layout(location = 1) uniform mat4 uProjection;

void main()
{
	TexCoords = vertex.zw;
    gl_Position = uProjection * vec4(vertex.xy, 0.0, 1.0);
}
)""