#include "Shape.h"


Shape::Shape(void)
{
	vertices = 0;
	indices = 0;
	numVerts = 0;
	numInds = 0;
	vbo = 0;
	ibo = 0;
}

Shape::Shape(Vertex* _verts, unsigned int* _inds, int _nverts, int _ninds)
{
	vertices = _verts;
	indices = _inds;
	numVerts = _nverts;
	numInds = _ninds;
	vbo = 0;
	ibo = 0;

	generateBuffers();
}


Shape::~Shape(void)
{
	if (vertices) delete[] vertices;
	if (indices) delete[] indices;
	if (vbo) glDeleteBuffers(1, &vbo);
	if (ibo) glDeleteBuffers(1, &ibo);
}

void Shape::generateBuffers()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVerts, vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numInds, indices, GL_STATIC_DRAW);
}

void Shape::bindIndices()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numInds, indices, GL_STATIC_DRAW);
}

GLuint Shape::getVBO() { return vbo; }

GLuint Shape::getIBO() { return ibo; }

unsigned int Shape::getNumInds() { return numInds; }

int Shape::getNumVerts() { return numVerts; }
