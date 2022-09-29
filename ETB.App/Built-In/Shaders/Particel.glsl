varying vec2 uvMainTex;
uniform sampler2D texture;

#ifdef ETB_VERTEX_SHADER

layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec2 _uvMainTex;
layout (location = 2) in vec3 _vertexNormal;

void main() {
	uvMainTex = _uvMainTex;
	gl_Position = vec4(_vertexPosition * 2, 1);
}

#endif
#ifdef ETB_FRAGMENT_SHADER

void main() {
	vec3 color = texture(texture, uvMainTex).rgb;
	
	gl_FragColor = vec4(color, 1);
}

#endif