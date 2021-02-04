#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 positionAndScale;
layout(location = 2) in vec4 color;

layout(binding = 0, std140) uniform Matrices
{
	mat4 uModel;
	mat4 uView;
	mat4 uInvView;
	mat4 uProjection;
	mat4 uLightViewProjection;
};

out vec2 TexCoords;
out vec4 Color;

void main()
{
    vec3 cameraRight = vec3(uView[0][0], uView[1][0], uView[2][0]);
    vec3 cameraUp = vec3(uView[0][1], uView[1][1], uView[2][1]);

    TexCoords = position.xy + vec2(0.5, 0.5);
	Color = color;

    vec3 worldPosition = positionAndScale.xyz + cameraRight * position.x * positionAndScale.w + 
        cameraUp * position.y * positionAndScale.w;

    gl_Position = uProjection * uView * vec4(worldPosition, 1.0);
}