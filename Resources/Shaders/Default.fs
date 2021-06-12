// Copyright Reality Engine. All Rights Reserved.

#version 440 core

out vec3 FragColor;

#define PI 3.14159265359
#define LIGHT_MAX_SIZE 100
#define LIGHT_LINEAR 0.07
#define LIGHT_QUADRATIC 0.017
#define LIGHT_AMBIENT 0.2

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 ViewPos;
	vec3 ViewDir;
	mat3 Tbn;
} fs_in;

#define TEXTURE_ALBEDO_MASK 1 << 0
#define TEXTURE_SPECULAR_MASK 1 << 1
#define TEXTURE_NORMAL_MASK 1 << 2
#define TEXTURE_HEIGHT_MASK 1 << 3

struct Material
{
	int TextureMask;
	vec3 Color;
	vec3 SpecularStrength;
	sampler2D Albedo;
	sampler2D Specular;
	sampler2D Normal;
	sampler2D Height;
	float Shininess;
};

#define LIGHT_DIRECTIONAL_TYPE 0
#define LIGHT_POINT_TYPE 1
#define LIGHT_SPOT_TYPE 2

struct Light
{
	vec4 Color;
	vec4 Position;
	vec4 Direction;
	int Type;
	float Intensity;
	float Cutoff;
	float Outcutoff;
};

layout (binding = 1, std140) buffer Lights
{
	Light uLights[];
};

uniform Material uMaterial;
uniform int uNumberOfLights;

vec3 DirectionalLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
vec3 PointLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
vec3 SpotLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
	vec2 texCoords = fs_in.TexCoords;
	if ((uMaterial.TextureMask & TEXTURE_HEIGHT_MASK) > 0)
	{
		texCoords = ParallaxMapping(fs_in.TexCoords, fs_in.ViewDir);
		if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		{
			discard;
		}
	}

	vec3 diffuse = (uMaterial.TextureMask & TEXTURE_ALBEDO_MASK) > 0 ? texture(uMaterial.Albedo, texCoords).rgb : vec3(1.0, 0.0, 1.0);
	vec3 specular = (uMaterial.TextureMask & TEXTURE_SPECULAR_MASK) > 0 ? texture(uMaterial.Specular, texCoords).rgb : vec3(0.0);
	vec3 normal = (uMaterial.TextureMask & TEXTURE_NORMAL_MASK) > 0 ? 
		normalize(fs_in.Tbn * (2.0 * texture(uMaterial.Normal, texCoords).rgb - 1.0)) : fs_in.Normal;

	diffuse *= uMaterial.Color;
	specular *= uMaterial.SpecularStrength;

	for (int i = 0; i < uNumberOfLights; i++)
	{
		switch (uLights[i].Type)
		{
			case LIGHT_DIRECTIONAL_TYPE:
				FragColor += DirectionalLight(uLights[i], diffuse, specular, normal) * uLights[i].Intensity;
				break;
			case LIGHT_POINT_TYPE:
				FragColor += PointLight(uLights[i], diffuse, specular, normal) * uLights[i].Intensity;
				break;
			case LIGHT_SPOT_TYPE:
				FragColor += SpotLight(uLights[i], diffuse, specular, normal) * uLights[i].Intensity;
				break;
		}
	}

	FragColor += diffuse * LIGHT_AMBIENT;
}

vec3 DirectionalLight(Light light, vec3 diffuse, vec3 specular, vec3 normal)
{
    vec3 lightDir = normalize(-light.Direction.xyz);
    vec3 diff = max(dot(normal, lightDir), 0.0) * diffuse * light.Color.rgb;
    vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) * specular;
    return diff + spec;
}

vec3 PointLight(Light light, vec3 diffuse, vec3 specular, vec3 normal)
{
    vec3 lightDir = normalize(light.Position.xyz - fs_in.FragPos); 
    float distance = length(light.Position.xyz - fs_in.FragPos);
    float attenuation = 1.0 / (1.0 + LIGHT_LINEAR * distance + LIGHT_QUADRATIC * (distance * distance));
    vec3 diff = max(dot(normal, lightDir), 0.0) * diffuse * light.Color.rgb * attenuation;
    vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) * specular * attenuation;
    return diff + spec;
}

vec3 SpotLight(Light light, vec3 diffuse, vec3 specular, vec3 normal)
{
    vec3 lightDir = normalize(light.Position.xyz - fs_in.FragPos);	
	float distance = length(light.Position.xyz - fs_in.FragPos);
    float attenuation = 1.0 / (1.0 + LIGHT_LINEAR * distance + LIGHT_QUADRATIC * (distance * distance));
    float theta = dot(lightDir, normalize(-light.Direction.xyz));
	float epsilon = cos(radians(light.Cutoff)) - cos(radians(light.Outcutoff));
    float intensity = clamp((theta - cos(radians(light.Outcutoff))) / epsilon, 0.0, 1.0);
    vec3 diff = max(dot(normal, lightDir), 0.0) * diffuse * light.Color.rgb * attenuation * intensity;
    vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) * specular * attenuation * intensity;
    return diff + spec;
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir)
{ 
    const float minLayers = 8;
    const float maxLayers = 32;
    float numLayers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), viewDir)));  
    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy / viewDir.z * 0.1f; 
    vec2 deltaTexCoords = P / numLayers;

    vec2  currentTexCoords = texCoords;
    float currentDepthMapValue = texture(uMaterial.Height, currentTexCoords).r;
      
    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(uMaterial.Height, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }
    
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(uMaterial.Height, prevTexCoords).r - currentLayerDepth + layerDepth;
 
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
}
