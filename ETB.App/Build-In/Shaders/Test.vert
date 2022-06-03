#version 330 core
layout (location = 0) in vec3 ETBVertexPosition;
layout (location = 1) in vec2 ETBTextcoordIn;
layout (location = 2) in vec3 ETBVertexNormal;

uniform mat4 ETBWorldMatrix;
uniform mat4 ETBModelMatrix;

varying vec2 ETBTextcoord;
varying vec4 VertexPosition;
varying vec3 Normal;

void main() {
	ETBTextcoord = ETBTextcoordIn;
	Normal = (ETBModelMatrix * vec4(normalize(ETBVertexNormal), 1.0)).xyz;
	
	VertexPosition = (ETBModelMatrix * vec4(ETBVertexPosition, 1));
	gl_Position = ETBWorldMatrix * VertexPosition;
}