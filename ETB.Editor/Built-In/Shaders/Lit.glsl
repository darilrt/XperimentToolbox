#ifdef ETB_VERTEX_SHADER

#version 400
varying vec2 uvMainTex;
varying vec4 vertexPosition;
varying vec3 worldNormal;

uniform mat4 ETB_MATRIX_VP; // View * Projection Matrix
uniform mat4 ETB_MATRIX_M;  // Model View Matrix

uniform vec3 _ScreenResolution;  // World Camera Position
uniform vec3 _worldCameraPos;  // World Camera Position

uniform sampler2D _BaseColor;
uniform sampler2D _NormalMap;
uniform sampler2D _MetallicMap;
uniform sampler2D _RoughnessMap;
uniform sampler2D _SpecularMap;
uniform sampler2D _AoMap;

uniform float _Specular;
uniform float _Roughness;
uniform float _Metalic;
uniform float _Normal;

////////////////////////////////////////////////////////

vec3 direccionalLight = vec3(1, 0, 0);
vec3 normal;

const float PI = 3.14159265359;
float roughness = 0.1;
float metallic = 0.1;
float specular = 1.0;
float normalStrenght = 1;
float ao = 1;

vec3 GetNormalFromMap() {
    vec3 tangentNormal = texture(_NormalMap, uvMainTex).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(vertexPosition.xyz);
    vec3 Q2  = dFdy(vertexPosition.xyz);
    vec2 st1 = dFdx(uvMainTex);
    vec2 st2 = dFdy(uvMainTex);

    vec3 N   = normalize(worldNormal);
    vec3 T  = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float a) {
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float nom    = a2;
    float denom  = (NdotH2 * (a2 - 1.0) + 1.0);
    denom        = PI * denom * denom;
	
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float k) {
    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return nom / denom;
}
  
float GeometrySmith(vec3 N, vec3 V, vec3 L, float k) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, k);
    float ggx2 = GeometrySchlickGGX(NdotL, k);
	
    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 GetSpecular(vec3 A, float S, vec3 _N) {
	vec3 N = normalize(_N);
	vec3 V = normalize(_worldCameraPos - vertexPosition.xyz);
	vec3 L = -direccionalLight;
	vec3 H = normalize(V + L);
	vec3 F0 = vec3(0.4);
	
	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);
	vec3  F = FresnelSchlick(max(dot(H, V), 0.0), F0);
	
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	kD *= 1.0 - metallic;
	
	vec3 numerator    = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
	vec3 specular     = numerator / denominator;  
		
	float NdotL = max(dot(N, L), 0.0);
	return (kD * A / PI + (specular * S)) * NdotL;
}

vec3 Render(vec2 uvMap) {
	/// Get maps
	vec3 albedo = pow(texture(_BaseColor, uvMap).rgb, vec3(2.2));
	
	metallic = _Metalic;
	roughness = _Roughness;
	specular = _Specular;
	
	normal = GetNormalFromMap();
	metallic = 1.0 - texture(_MetallicMap, uvMap).r;
	roughness = texture(_RoughnessMap, uvMap).r;
	// specular = texture(_BaseColor, uvMap).r;
	// ao = texture(_AoMap, uvMap).r;
	
	////////////////////////////////////////////////////////////////////
	
    vec3 ambient = vec3(0.00) * albedo * ao;
	vec3 Lo = GetSpecular(albedo, specular, normal);
	
	vec3 color = ambient + Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.0));  
	
	return color;
}

void main() {
	gl_FragColor = vec4(Render(uvMainTex), 1);
}

#endif
#ifdef ETB_FRAGMENT_SHADER

#version 330 core
layout (location = 0) in vec3 _vertexPosition;
layout (location = 1) in vec2 _uvMainTex;
layout (location = 2) in vec3 _vertexNormal;

uniform mat4 ETB_MATRIX_VP; // View * Projection Matrix
uniform mat4 ETB_MATRIX_M;  // Model View Matrix

uniform vec3 _worldCameraPos;  // World Camera Position

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

#endif