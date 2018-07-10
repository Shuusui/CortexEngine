#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    mat3 MV3x3;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBitangent;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
layout(location = 3) out vec3 lightDirectionCS;

out gl_PerVertex {
    vec4 gl_Position;
};

void main() {
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);

	vec3 inPositionWS = (ubo.model*vec4(inPosition,1)).xyz;

	vec3 inPositionCS = (ubo.view*ubo.model*vec4(inPosition,1)).xyz;
	vec3 viewDirCS = vec3(0,0,0) - inPositionCS;

	vec3 lightPosCS = (ubo.view*vec4(100,50,-50,1)).xyz;
	
	vec3 inNormalCS = ubo.MV3x3 * normalize(inNormal); 
	vec3 inTangentCS = ubo.MV3x3 * normalize(inTangent); 
	vec3 inBitangentCS = ubo.MV3x3 * normalize(inBitangent); 

	mat3 TBN = transpose(mat3(inTangentCS, inBitangentCS, inNormalCS)); 
	

	vec3 lightDirectionCS = normalize(lightPosCS+viewDirCS);

	vec3 lightDirectionTS = TBN * normalize(lightDirectionCS);
	
	vec3 viewDirTS = TBN * viewDirCS; 

	fragNormal = normalize(ubo.view*ubo.model*vec4(inNormal,0)).xyz;

    fragColor = inColor;
    fragTexCoord = inTexCoord;

}