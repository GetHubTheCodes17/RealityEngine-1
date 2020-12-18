R""(
#version 440 core

out vec3 FragColor;
noperspective in vec2 TexCoords;

layout(binding = 0) uniform sampler2D uImage;

uniform int uGhosts = 12;
uniform float uGhostDispersal = 0.2;
uniform float uDistortion = 5.0;
uniform float uHaloWidth = 0.5;

vec3 TextureDistorted(vec2 texCoords, vec2 direction, vec3 distortion);
vec3 DrawGhost(vec2 texCoords, vec2 texelSize, vec2 ghostVec, vec3 distortion, vec2 direction);

void main() 
{
    vec2 texelSize = 1.0 / vec2(textureSize(uImage, 0)); 
    vec2 ghostVec = (vec2(0.5) - TexCoords) * uGhostDispersal;
    vec3 distortion = vec3(-texelSize.x * uDistortion, 0.0, texelSize.x * uDistortion);
    vec2 direction = normalize(ghostVec); 

    vec3 result = DrawGhost(TexCoords, texelSize, ghostVec, distortion, direction);

    vec2 haloVec = direction * uHaloWidth;
    float weight = length(vec2(0.5) - fract(TexCoords + haloVec)) / length(vec2(0.5));
    weight = pow(1.0 - weight, 5.0);
    result += TextureDistorted(TexCoords + haloVec, direction, distortion) * weight;

    FragColor = result;
}

vec3 DrawGhost(vec2 texCoords, vec2 texelSize, vec2 ghostVec, vec3 distortion, vec2 direction)
{
    vec3 result = vec3(0.0);

    for (int i = 0; i < uGhosts; ++i) 
    { 
        vec2 offset = fract(texCoords + ghostVec * float(i));    
        float weight = length(vec2(0.5) - offset) / length(vec2(0.5));
        weight = pow(1.0 - weight, 10.0);  
        result += TextureDistorted(offset, direction, distortion) * weight;
    }

    return result;
}

vec3 TextureDistorted(vec2 texCoords, vec2 direction, vec3 distortion) 
{
    return vec3
    (
        texture(uImage, texCoords + direction * distortion.r).r,
        texture(uImage, texCoords + direction * distortion.g).g,
        texture(uImage, texCoords + direction * distortion.b).b
    );
}
)""