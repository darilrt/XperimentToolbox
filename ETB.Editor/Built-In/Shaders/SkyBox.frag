#version 330 core
varying vec2 uvMainTex;
varying vec4 vertexPosition;
varying vec3 worldNormal;

uniform mat4 ETB_MATRIX_VP; // View * Projection Matrix
uniform mat4 ETB_MATRIX_M;  // Model View Matrix

uniform sampler2D _BaseColor;

vec3 lightPos = vec3(-3, 0, 2);
vec3 lightColor = vec3(1, 1, 1);

///////////////////////////////////////////////////////////////

void main() {
	vec3 objectColor = texture(_BaseColor, uvMainTex).xyz;
	
	gl_FragColor = vec4(objectColor , 1.0);
}