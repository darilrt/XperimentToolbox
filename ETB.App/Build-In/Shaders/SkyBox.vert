#version 330 core
layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec2 _uvMainTex;
layout (location = 2) in vec3 _vertexNormal;

uniform mat4 ETB_MATRIX_VP; // View * Projection Matrix
uniform mat4 ETB_MATRIX_M;  // Model View Matrix

varying vec2 uvMainTex;
varying vec4 vertexPosition;
varying vec3 worldNormal;

////////////////////////////////////////////////////////

void main() {
	uvMainTex = _uvMainTex;
	worldNormal = (ETB_MATRIX_M * vec4(normalize(_vertexNormal), 1.0)).xyz;
	vertexPosition = ETB_MATRIX_M * vec4(_vertexPosition, 1);
	
	gl_Position = ETB_MATRIX_VP * vertexPosition;
}