#version 400
varying vec2 textcoord;
uniform float radius;

void main() {
	textcoord = gl_MultiTexCoord0.xy;

	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * (gl_Vertex * vec4(radius, radius, 1, 1));
}
