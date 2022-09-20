#version 400
varying vec2 textcoord;
uniform vec3 color;
uniform vec3 strokeColor;
uniform float stroke;
uniform float radius;

void main() {
	float l = length(textcoord - vec2(0.5, 0.5)) / 0.5;
	
	if (l > 1) {
		discard;
	}
	
	float r2 = radius;
	float sd = l * radius;
	
	if (sd > radius - stroke * 2) {
		gl_FragColor = vec4(0, 0, 0, 1);
	}
	else {
		gl_FragColor = vec4(color, 1);
	}
}
