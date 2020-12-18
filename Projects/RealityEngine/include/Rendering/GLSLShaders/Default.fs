R""( 
#version 440 core

layout(location = 0) out vec3 FragColor;
layout(location = 1) out vec3 BrightColor;

#define PI 3.14159265359
#define LIGHT_MAX_SIZE 100
#define LIGHT_LINEAR 0.07
#define LIGHT_QUADRATIC 0.017
#define LIGHT_AMBIENT 0.2

in VS_OUT
{
	vec3 FragPos;
	vec4 FragPosLightSpace;
	vec3 Normal;
	vec2 TexCoords;
	vec3 ViewPos;
	vec3 ViewDir;
	mat3 Tbn;
} fs_in;

#define LIGHT_DIRECTIONAL_TYPE 0
#define LIGHT_POINT_TYPE 1
#define LIGHT_SPOT_TYPE 2

#define LIGHT_SHADOW_NONE 0
#define LIGHT_SHADOW_SOFT 1

struct Light
{
	vec4 Color;
	vec4 Position;
	vec4 Direction;
	int Type;
	int Shadow;
	float Intensity;
	float Cutoff;
	float Outcutoff;
};

layout(binding = 1, std430) buffer Lights
{
	uint uNumberOfLights;
	Light uLights[];
};

#define TEXTURE_ALBEDO_MASK 1 << 0
#define TEXTURE_SPECULAR_MASK 1 << 1
#define TEXTURE_NORMAL_MASK 1 << 2
#define TEXTURE_HEIGHT_MASK 1 << 3
#define TEXTURE_REFLECTION_MASK 1 << 4
#define TEXTURE_EMISSIVE_MASK 1 << 5

struct Material
{
	int Mask;
	vec3 Color;
	vec3 SpecularStrength;
	float Shininess;
};

layout(location = 2) uniform Material uMaterial;
layout(location = 6) uniform float uBias = 0.0005;

layout(binding = 0) uniform sampler2D uAlbedo;
layout(binding = 1) uniform sampler2D uSpecular;
layout(binding = 2) uniform sampler2D uNormal;
layout(binding = 3) uniform sampler2D uHeight;
layout(binding = 4) uniform sampler2D uReflection;
layout(binding = 5) uniform sampler2D uEmissive;

layout(binding = 6) uniform samplerCube uSkybox;
layout(binding = 7) uniform sampler2D uShadowMap;

vec3 DirectionalLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
vec3 PointLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
vec3 SpotLight(Light light, vec3 diffuse, vec3 specular, vec3 normal);
float ShadowCalculationDirLight(Light light, vec3 normal);
vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main()
{
	vec2 texCoords = fs_in.TexCoords;
	if ((uMaterial.Mask & TEXTURE_HEIGHT_MASK) > 0)
	{
		texCoords = ParallaxMapping(fs_in.TexCoords, fs_in.ViewDir);
		if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		{
			discard;
		}
	}

	vec3 diffuse = (uMaterial.Mask & TEXTURE_ALBEDO_MASK) > 0 ? 
		texture(uAlbedo, texCoords).rgb * uMaterial.Color: uMaterial.Color;
	vec3 specular = (uMaterial.Mask & TEXTURE_SPECULAR_MASK) > 0 ? 
		texture(uSpecular, texCoords).rgb : vec3(0.3, 0.3, 0.3);
	vec3 normal = (uMaterial.Mask & TEXTURE_NORMAL_MASK) > 0 ? 
		normalize(fs_in.Tbn * (2.0 * texture(uNormal, texCoords).rgb - 1.0)) : fs_in.Normal;

	specular *= uMaterial.SpecularStrength;

	for (int i = 0; i < uNumberOfLights; ++i)
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

	if ((uMaterial.Mask & TEXTURE_REFLECTION_MASK) > 0)
	{
		vec3 I = normalize(fs_in.FragPos - fs_in.ViewPos);
		vec3 R = reflect(I, normalize(normal));
		vec3 reflCol = texture(uSkybox, R).rgb;
		vec3 reflTex = texture(uReflection, texCoords).rgb;
		FragColor += reflCol * reflTex;
	}

	if ((uMaterial.Mask & TEXTURE_EMISSIVE_MASK) > 0)
	{
		BrightColor = texture(uEmissive, texCoords).rgb;
	}
	else
	{
		float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
		BrightColor = brightness > 5.0 ? FragColor.rgb : vec3(0.0, 0.0, 0.0);
	}

	FragColor += diffuse * LIGHT_AMBIENT;
}

vec3 DirectionalLight(Light light, vec3 diffuse, vec3 specular, vec3 normal)
{
	vec3 lightDir = normalize(-light.Direction.xyz);
	vec3 diff = max(dot(normal, lightDir), 0.0) * diffuse * light.Color.rgb;
	vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) * specular;

	if (light.Shadow == LIGHT_SHADOW_SOFT)
	{
		return ((1.0 - ShadowCalculationDirLight(light, normal)) * (diff + spec));
	}

	return diff + spec;
}

vec3 PointLight(Light light, vec3 diffuse, vec3 specular, vec3 normal)
{
	vec3 lightDir = normalize(light.Position.xyz - fs_in.FragPos); 
	float distance = length(light.Position.xyz - fs_in.FragPos);
	float attenuation = 1.0 / (1.0 + LIGHT_LINEAR * distance + LIGHT_QUADRATIC * (distance * distance));
	vec3 diff = max(dot(normal, lightDir), 0.0) * diffuse * light.Color.rgb * attenuation;
	vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) 
		* specular * attenuation;
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
	vec3 spec = pow(max(dot(normal, normalize(lightDir + fs_in.ViewDir)), 0.0), uMaterial.Shininess) 
		* specular * attenuation * intensity;
	return diff + spec;
}

float ShadowCalculationDirLight(Light light, vec3 normal)
{
	vec3 projCoords = fs_in.FragPosLightSpace.xyz / fs_in.FragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	if (projCoords.z > 1.0)
	{
		return 0.0;
	}

	vec3 lightDir = normalize(light.Position.xyz - fs_in.FragPos);

	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(uShadowMap, 0);

	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; y++)
		{
			float pcfDepth = texture(uShadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += projCoords.z - uBias > pcfDepth  ? 1.0 : 0.0;    
		}    
	}
	shadow /= 9.0;
        
	return shadow;
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
	float currentDepthMapValue = texture(uHeight, currentTexCoords).r;
      
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(uHeight, currentTexCoords).r;  
		currentLayerDepth += layerDepth;  
	}
    
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(uHeight, prevTexCoords).r - currentLayerDepth + layerDepth;
 
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;
}
)""