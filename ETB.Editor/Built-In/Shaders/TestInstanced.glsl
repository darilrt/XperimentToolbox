uniform mat4 ETB_MATRIX_VP; // View * Projection Matrix
uniform mat4 ETB_MATRIX_M;  // Model View Matrix

uniform sampler2D albedo;

varying vec2 uvMainTex;
varying vec4 vertexPosition;
varying vec3 worldNormal;

#ifdef ETB_VERTEX_SHADER

layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec2 _uvMainTex;
layout (location = 2) in vec3 _vertexNormal;

void main() {
	uvMainTex = _uvMainTex;
	worldNormal = (ETB_MATRIX_M * vec4(normalize(_vertexNormal), 1.0)).xyz;
	vertexPosition = ETB_MATRIX_M * vec4(_vertexPosition, 1);
	
	gl_Position = ETB_MATRIX_VP * vertexPosition;
}

#endif
#ifdef ETB_FRAGMENT_SHADER

vec3 lightPos = vec3(-3, 2.5f, 2);
vec3 lightColor = vec3(1, 1, 1);

void main() {
	vec3 objectColor = texture(albedo, uvMainTex).rgb;
	
	// ambient
    float ambientstrength = 0.1;
    vec3 ambient = ambientstrength * lightColor;
	
	// diffuse
	vec3 norm = normalize(worldNormal);
	vec3 lightdir = normalize(lightPos);
	
	float diff = max(dot(norm, lightdir), 0.0);
	vec3 diffuse = diff * lightColor;
	
    vec3 result = (ambient + diffuse) * objectColor;
	
	gl_FragColor = vec4(result, 1.0);
}

#endif