#version 400
varying vec2 textcoord;
varying vec3 normal;
uniform sampler2D texture;

void main() {
	vec4 color = texture2D(texture, textcoord);
	
	gl_FragColor = vec4(textcoord, 0, 1);
}
