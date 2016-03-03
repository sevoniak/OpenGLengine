#pragma once

#include <glew.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Shader
{
private:
	string filename;
	string vertSource;
	string fragSource;
	string geomSource;
	GLuint vertShader;
	GLuint fragShader;
	GLuint geomShader;
	GLuint shaderProgram;
	bool validated;

	string loadFile(string fName);
	void linkShaders();
	bool validateShaders();

public:
	Shader(void);
	Shader(string);
	~Shader(void);

	GLuint getProgram();
	bool isValid();
};

