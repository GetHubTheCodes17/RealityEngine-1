#version 440 core

out vec3 FragColor;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uImage;

layout(location = 1) uniform bool uHorizontal;
uniform float uWeight[5] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{             
	vec2 tex_offset = 1.0 / textureSize(uImage, 0);
	vec3 result = texture(uImage, TexCoords).rgb * uWeight[0];
	if(uHorizontal)
	{
		for(int i = 1; i < 5; ++i)
		{
			result += texture(uImage, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * uWeight[i];
			result += texture(uImage, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * uWeight[i];
		}
	}
	else
	{
		for(int i = 1; i < 5; ++i)
		{
			result += texture(uImage, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * uWeight[i];
			result += texture(uImage, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * uWeight[i];
		}
	}
	FragColor = result;
}