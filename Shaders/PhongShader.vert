#version 440

struct LightInfo {
	vec3 Lpos;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 vMatrix;
uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;

uniform LightInfo Linfo;

out vec3 vertPosCS;
out vec3 vertNormCS;
out vec3 lightPosCS;

void main()
{	
	vertPosCS = vec3(mvMatrix * vec4(position, 1.0));
	vertNormCS = transpose(inverse(mat3(mvMatrix))) * normal;
	lightPosCS = vec3(vMatrix * vec4(Linfo.Lpos, 1.0));

	gl_Position = mvpMatrix * vec4(position, 1.0);
}