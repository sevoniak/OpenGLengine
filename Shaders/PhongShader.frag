#version 440

struct LightInfo {
	vec3 Lpos;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	int shine;
};

in vec3 vertPosCS;
in vec3 vertNormCS;
in vec3 lightPosCS;

uniform LightInfo Linfo;
uniform MaterialInfo Minfo;

out vec4 finalColor;

void main()
{
	vec3 L, N, V, R;
	
	N = normalize(vertNormCS);
	V = -vertPosCS;
	V = normalize(V);
	L = lightPosCS - vertPosCS;
	L = normalize(L);

	//Diffuse
	float Id = clamp(dot(N,L), 0.0, 1.0);
	vec3 KdLd = Minfo.Kd * Linfo.Ld;

	//Specular
	R = 2*dot(L,N)*N - L;
	float Is = clamp(dot(V,R), 0.0, 1.0);
	Is = pow(Is, Minfo.shine);
	vec3 KsLs = Minfo.Ks * Linfo.Ls;
	
	//Ambient
	float Ia = 0.1f;
	vec3 KaLa = Minfo.Ka * Linfo.La;

	//Intensity
	vec3 I = Id*KdLd + Is*KsLs + Ia*KaLa;

	finalColor = vec4(I, 1.0);
}