#version 440 core

uniform mat4 uView;
uniform mat4 uMV;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

uniform float uTime;
uniform float uWaveSpeed;
uniform float uWaveHeight;
uniform float uWaveFrequency;
uniform bool uDistortionEnabled;

in vec4 vPosition;
in vec2 vTexCoord;
in vec3 vNormal;

out vec2 texCoord;
out vec3 positionEyeSpace;
out vec3 normalEyeSpace;

vec4 calculateWaveDistortion(vec3 position, vec3 normal,  float yOffset, float height, float frequency);

void main()
{ 
	vec4 distortedPos = vPosition;

	if(uDistortionEnabled){
		distortedPos = calculateWaveDistortion(
			vPosition.xyz, vNormal, uWaveSpeed * uTime, 
			uWaveHeight, uWaveFrequency
		);
	}

	gl_Position = uMVP * distortedPos;

	texCoord = vTexCoord;

	positionEyeSpace = (uMV * vPosition).xyz;

	normalEyeSpace = normalize(uNormalMatrix * vNormal);
}

vec4 calculateWaveDistortion(vec3 position, vec3 normal, float yOffset, float height, float frequency) {
	return vec4(position + height * sin(frequency * position.y + yOffset) * normal, 1.0f);
}