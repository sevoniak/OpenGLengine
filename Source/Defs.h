#pragma once

// INCLUDES
#include <glew.h>
#include "Mathlib.h"
#include <string>
using std::string;

// DEFINES

#define SPEED_STRAFE 0.002f
#define SPEED_ROTATE 0.0003f

#define NUMSHADERS 4
#define SHADER_BASIC 0
#define SHADER_COLOR 1
#define SHADER_GOURAUD 2
#define SHADER_PHONG 3

#define NUMSHAPES 6
#define SHAPE_QUAD 0
#define SHAPE_CUBE 1
#define SHAPE_CONE 2
#define SHAPE_PRISM 3
#define SHAPE_SPHERE 4
#define SHAPE_TORUS 5


// TYPEDEFS and STRUCTS
typedef struct vertex {
	Vector3 position;
	Vector3 normal;

	vertex(Vector3 _pos, Vector3 _norm):
		position(_pos), normal(_norm)
	{}

	vertex():
		position(Vector3(0,0,0)), normal(Vector3(0,0,0))
	{}
} Vertex;

typedef struct windowinfo {
	int width;
	int height;
	float aspectRatio;
	float FoV_Y;
	float zNear;
	float zFar;
	string title;
	GLuint windowID;
} WindowInfo;

typedef struct vector4 {
	float r;
	float g;
	float b;
	float a;

	vector4():
		r(0), g(0), b(0), a(1)
	{}
	vector4(float _r, float _g, float _b, float _a):
		r(_r), g(_g), b(_b), a(_a)
	{}
} Vector4;

typedef struct vector2 {
	float u;
	float v;

	vector2(float _u, float _v):
		u(_u), v(_v)
	{}
} Vector2;

typedef struct lightInfo {
	Vector3 Lpos;
	Vector3 La;
	Vector3 Ld;
	Vector3 Ls;

	lightInfo():
		Lpos(Vector3(0,0,0)), La(Vector3(0.9f,0,0)), Ld(Vector3(0,0,0.9f)), Ls(Vector3(1,1,1))
	{}
	lightInfo(Vector3 _pos):
		Lpos(_pos), La(Vector3(0.9f,0,0)), Ld(Vector3(0,0,0.9f)), Ls(Vector3(1,1,1))
	{}
} LightInfo;

typedef struct materialInfo {
	Vector3 Ka;
	Vector3 Kd;
	Vector3 Ks;
	int shine;

	materialInfo():
		Ka(Vector3(1,1,1)), Kd(Vector3(1,1,1)), Ks(Vector3(1,1,1)), shine(35)
	{}
	materialInfo(Vector3 _ka, Vector3 _kd, Vector3 _ks, int _shine):
		Ka(_ka), Kd(_kd), Ks(_ks), shine(_shine)
	{}
} MaterialInfo;