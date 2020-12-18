R""(	
#version 440 core

layout(location = 0) in vec3 position;

layout(binding = 0, std140) uniform Matrices
{
	mat4 uModel;
	mat4 uView;
	mat4 uInvView;
	mat4 uProjection;
	mat4 uLightViewProjection;
};

out vec3 TexCoords;

void main()
{
	TexCoords = position;
	gl_Position = (uProjection * mat4(mat3(uView)) * vec4(position, 1.0)).xyww;
}
)""