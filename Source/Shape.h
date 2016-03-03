#pragma once
#include "Defs.h"

class Shape
{
private:
	Vertex* vertices;
	unsigned int* indices;
	int numVerts;
	int numInds;
	GLuint vbo;
	GLuint ibo;

	void generateBuffers();

public:
	Shape(void);
	Shape (Vertex*, unsigned int*, int, int);
	~Shape(void);

	GLuint getVBO();
	GLuint getIBO();
	unsigned int getNumInds();
	int getNumVerts();

	void bindIndices();
};

