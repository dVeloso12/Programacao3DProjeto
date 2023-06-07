#version 440 core

struct AmbientLight {
	vec3 ambient;

	bool enabled;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool enabled;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;

	bool enabled;
};

struct SpotLight {
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;

	float spotCutoff;
	float spotExponent;

	bool enabled;
};

struct Material {
	vec3 emissive;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform mat4 uView;
uniform sampler2D uTexSampler;

// Lights
uniform AmbientLight uAmbientLight;
uniform DirectionalLight uDirectionalLight;
uniform PointLight uPointLight;
uniform SpotLight uSpotLight;

// Material
uniform Material uMaterial;

in vec2 texCoord;
in vec3 positionEyeSpace;
in vec3 normalEyeSpace;

out vec4 fColor;

vec4 calculateAmbientLight(AmbientLight light);
vec4 calculateDirectionalLight(DirectionalLight light);
vec4 calculatePointLight(PointLight light);
vec4 calculateSpotLight(SpotLight light);

float map(float value, float min1, float max1, float min2, float max2);

void main()
{
	vec4 texColor = texture(uTexSampler, texCoord);

	vec4 ambient = calculateAmbientLight(uAmbientLight);

	vec4 directional = calculateDirectionalLight(uDirectionalLight);

	vec4 point = calculatePointLight(uPointLight);

	vec4 spot = calculateSpotLight(uSpotLight);

	fColor = (vec4(uMaterial.emissive, 1.0f) + ambient + directional + point + spot) * texColor;
}

vec4 calculateAmbientLight(AmbientLight light) {
	if(!light.enabled) return vec4(0.0f);

	return vec4(uMaterial.ambient * light.ambient, 1.0f);
}

vec4 calculateDirectionalLight(DirectionalLight light) {
	if(!light.enabled) return vec4(0.0f);

	vec4 ambient = vec4(uMaterial.ambient * light.ambient, 1.0f);

	vec3 lightDirectionEyeSpace = (uView * vec4(light.direction, 0.0f)).xyz;
	vec3 lightInvDir = normalize(-lightDirectionEyeSpace);
	float nDotL = max(dot(normalEyeSpace, lightInvDir), 0.0f);
	vec4 diffuse = vec4(uMaterial.diffuse * light.diffuse * nDotL, 1.0f);
	
	vec3 pos = normalize(-positionEyeSpace);
	vec3 reflection = reflect(-lightInvDir, normalEyeSpace);
	float rDotV = max(dot(reflection, pos), 0.0f);
	vec4 specular = pow(rDotV, uMaterial.shininess) * vec4(light.specular * uMaterial.specular, 1.0f);

	return ambient + diffuse + specular;
}

vec4 calculatePointLight(PointLight light) {
	if(!light.enabled) return vec4(0.0f);
	
	vec4 ambient = vec4(uMaterial.ambient * light.ambient, 1.0f);

	vec3 lightPositionEyeSpace = (uView * vec4(light.position, 0.0f)).xyz;
	vec3 lightInvDir = normalize(lightPositionEyeSpace - positionEyeSpace);
	float nDotL = max(dot(normalEyeSpace, lightInvDir), 0.0f);
	vec4 diffuse = vec4(uMaterial.diffuse * light.diffuse * nDotL, 1.0f);
	
	vec3 pos = normalize(-positionEyeSpace);
	vec3 reflection = reflect(-lightInvDir, normalEyeSpace);
	float rDotV = max(dot(reflection, pos), 0.0f);
	vec4 specular = pow(rDotV, uMaterial.shininess) * vec4(light.specular * uMaterial.specular, 1.0f);

	float dist = length(mat3(uView) * light.position - positionEyeSpace);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	return attenuation * (ambient + diffuse + specular);
}

vec4 calculateSpotLight(SpotLight light) {
	if(!light.enabled) return vec4(0.0f);
	
	vec3 lightPositionEyeSpace = (uView * vec4(light.position, 0.0f)).xyz;
	vec3 lightInvDir = normalize(lightPositionEyeSpace - positionEyeSpace);

	vec3 spotLightDir = normalize(uView * vec4(light.direction, 0.0f)).xyz;

	float angleCos = dot(-spotLightDir, lightInvDir);

	if(angleCos < light.spotCutoff) {
		return vec4(0.0f);
	}

	vec4 ambient = vec4(uMaterial.ambient * light.ambient, 1.0f);

	float nDotL = max(dot(normalEyeSpace, lightInvDir), 0.0f);
	vec4 diffuse = vec4(uMaterial.diffuse * light.diffuse * nDotL, 1.0f);
	
	vec3 pos = normalize(-positionEyeSpace);
	vec3 reflection = reflect(-lightInvDir, normalEyeSpace);
	float rDotV = max(dot(reflection, pos), 0.0f);
	vec4 specular = pow(rDotV, uMaterial.shininess) * vec4(light.specular * uMaterial.specular, 1.0f);

	float dist = length(mat3(uView) * light.position - positionEyeSpace);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	attenuation *= pow(map(angleCos, light.spotCutoff, 1.0f, 0.0f, 1.0f), light.spotExponent);

	return attenuation * (ambient + diffuse + specular);
}

float map(float value, float min1, float max1, float min2, float max2) {
  return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}