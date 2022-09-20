varying vec2 uvMainTex;

uniform mat4 ETB_MATRIX_M;  // Model View Matrix

uniform vec2 _ScreenResolution;  // World Camera Position
uniform vec3 _worldCameraPos;  // World Camera Position

uniform sampler2D _ScreenColor;  // World Camera Position
uniform sampler2D _ScreenDepth;  // World Camera Position
uniform float _Time;  // World Camera Position

#ifdef ETB_FRAGMENT_SHADER

float LinearDepth(float d,float zNear, float zFar) {
    float z_n = 2.0 * d - 1.0;
    return (2.0 * zNear * zFar / (zFar + zNear - z_n * (zFar - zNear))) / zFar;
}

vec2 p = vec2(1, 1) / _ScreenResolution;
float kTexelSize = 1;
float fDepthThreshold = 0.01;
float fLuminanceThreshold = 1;

bool IsEdge() {
	float fDepth = texture(_ScreenDepth, uvMainTex).r;
	float fDepthLeft = texture(_ScreenDepth, uvMainTex + vec2(-p.x, 0.0)).r;
	float fDepthTop = texture(_ScreenDepth, uvMainTex + vec2(0.0, p.y)).r;
	
	vec2 kDepthDelta = abs(vec2(fDepth, fDepth) - vec2(fDepthLeft, fDepthTop));
	
	vec2 kEdges = step(vec2(fDepthThreshold, fDepthThreshold), kDepthDelta);
	
	float fLuminance = texture(_ScreenColor, uvMainTex).r;
	float fLuminanceLeft = texture(_ScreenColor, uvMainTex + vec2(-p.x, 0.0)).r;
	float fLuminanceTop = texture(_ScreenColor, uvMainTex + vec2(0.0, p.y)).r;
	vec2 kLuminanceDelta = abs(vec2(fLuminance, fLuminance) - vec2(fLuminanceLeft, fLuminanceTop));
	kEdges += step(vec2(fLuminanceThreshold, fLuminanceThreshold), kLuminanceDelta);
	
	return length(kEdges) > 0;
}

vec3 SSAAx4() {
	vec3 color = texture(_ScreenColor, uvMainTex).rgb;
	
	if (IsEdge()) {
		color += texture(_ScreenColor, uvMainTex + vec2(-p.x, -p.y)).rgb;
		color += texture(_ScreenColor, uvMainTex + vec2( p.x, -p.y)).rgb;
		color += texture(_ScreenColor, uvMainTex + vec2(-p.x,  p.y)).rgb;
		color += texture(_ScreenColor, uvMainTex + vec2( p.x,  p.y)).rgb;
		color /= 5.0;
	}
	
	return color;
}

void main() {
	vec3 color = texture(_ScreenColor, uvMainTex).rgb;
	float depth = LinearDepth(texture(_ScreenDepth, uvMainTex).r, 0.1, 100.0);
	
	gl_FragColor = vec4(SSAAx4(), 1);
}

#endif
#ifdef ETB_VERTEX_SHADER
layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec2 _uvMainTex;

void main() {
	uvMainTex = _uvMainTex;
	gl_Position = vec4(_vertexPosition * 2, 1);
}

#endif