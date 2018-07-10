#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform sampler2D normalSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 lightDirection;

layout(location = 0) out vec4 outColor;

void main() {
	vec4 lightColor = vec4(1,1,1,1);
	vec4 baseColor = texture(texSampler, fragTexCoord);
	vec3 texNormalTS = normalize(texture(normalSampler, fragTexCoord).rgb*2.0-1.0);
	
	float lightPower = 5;
	float cosTheta = clamp(dot(normalize(fragNormal),normalize(lightDirection)), 0, 1);
	vec4 matDiffCol = baseColor*cosTheta*lightColor*lightPower;

	vec4 matAmbCol = 0.1 *baseColor ;

	vec3 E = normalize(lightDirection);
	vec3 R = reflect(-lightDirection, fragNormal);
	float cosAlpha = clamp(dot(E,R), 0, 1);
	
	
	vec4 matSpecCol =  lightColor * lightPower* pow(cosAlpha, 60);
    outColor = matDiffCol+matAmbCol+texNormalTS;
}