#version 330 core
uniform mat4 ETBWorldMatrix;
uniform mat4 ETBModelMatrix;

uniform sampler2D BaseColor;

varying vec4 VertexPosition;
varying vec2 ETBTextcoord;
varying vec3 Normal;

vec3 lightPos = vec3(-3, 0, 2);
vec3 lightColor = vec3(1, 1, 1);

void main() {
	vec3 objectColor = texture(BaseColor, ETBTextcoord).xyz;
	
	// Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	
	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - VertexPosition.xyz);
	
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
    vec3 result = (ambient + diffuse) * objectColor;
	
	gl_FragColor = vec4(result, 1.0);
}