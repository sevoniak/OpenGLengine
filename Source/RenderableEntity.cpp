#include "RenderableEntity.h"


RenderableEntity::RenderableEntity(void)
{
	colors = 0;
	texCoords = 0;
	numColors = 0;
	numTexCoords = 0;
	texture = 0;
	shape = 0;
	shader = 0;
	cao = 0;
	tao = 0;
	vao = 0;
}

RenderableEntity::RenderableEntity(Shape* _shape, Shader* _shader)
{
	GLenum err = glGetError();
	const GLubyte* msg = gluErrorString(err);
	colors = 0;
	texCoords = 0;
	numColors = 0;
	numTexCoords = 0;
	texture = 0;
	shape = _shape;
	shader = _shader;
	cao = 0;
	tao = 0;
	vao = 0;
}

RenderableEntity::~RenderableEntity(void)
{
	if (colors) delete[] colors;
	if (texCoords) delete[] texCoords;
	if (cao) glDeleteBuffers(1, &cao);
	if (tao) glDeleteBuffers(1, &tao);
	if (vao) glDeleteBuffers(1, &vao);
}

void RenderableEntity::setColorless()
{
	initVAO();
}

void RenderableEntity::setColors(Vector4* _cols, int _ncols)
{
	colors = _cols;
	numColors = _ncols;
	initVAO();
}

void RenderableEntity::setTexture(Texture* _tex, Vector2* _coords, int _ncoords)
{
	texture = _tex;
	texCoords = _coords;
	numTexCoords = _ncoords;
	initVAO();
}

void RenderableEntity::initVAO()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	generateBuffers();
	bindShape();
	bindBuffers();
	GLenum err = glGetError();

	glBindVertexArray(0);
}

void RenderableEntity::generateBuffers()
{
	if (colors)
	{
		glGenBuffers(1, &cao);
		glBindBuffer(GL_ARRAY_BUFFER, cao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * numColors, colors, GL_STATIC_DRAW);
	}

	if (texCoords)
	{
		glGenBuffers(1, &tao);
		glBindBuffer(GL_ARRAY_BUFFER, tao);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * numTexCoords, texCoords, GL_STATIC_DRAW);
	}
}

void RenderableEntity::bindBuffers()
{
	if (colors)
	{
		glBindBuffer(GL_ARRAY_BUFFER, cao);
		GLuint loc = glGetAttribLocation(shader->getProgram(), "color");
		if (loc != -1)
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, sizeof(Vector4), 0);
		}
	}

	if (texCoords)
	{
		glBindBuffer(GL_ARRAY_BUFFER, tao);
		GLuint loc = glGetAttribLocation(shader->getProgram(), "texCoords");
		if (loc != -1)
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);
		}

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getBuffer());
		loc = glGetUniformLocation(shader->getProgram(), "texSamp");
		if (loc != -1)
			glUniform1i(loc, 0);
	}
}

void RenderableEntity::bindShape()
{
	Vertex v;
	glBindBuffer(GL_ARRAY_BUFFER, shape->getVBO());

	GLuint loc = glGetAttribLocation(shader->getProgram(), "position");
	if (loc != -1)
	{
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	loc = glGetAttribLocation(shader->getProgram(), "normal");
	if (loc != -1)
	{
		glEnableVertexAttribArray(loc);
		glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((int)&v.normal - (int)&v));
	}

	shape->bindIndices();
}

void RenderableEntity::bindMatrices(Matrix4& _vMat, Matrix4& _mvMat, Matrix4& _mvpMat)
{
	GLuint loc = glGetUniformLocation(shader->getProgram(), "mvMatrix");
	if (loc != -1)
		glUniformMatrix4fv(loc, 1, GL_TRUE, _mvMat.getFloats());

	loc = glGetUniformLocation(shader->getProgram(), "mvpMatrix");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_TRUE, _mvpMat.getFloats());
	}

	loc = glGetUniformLocation(shader->getProgram(), "vMatrix");
	if (loc != -1)
	{
		glUniformMatrix4fv(loc, 1, GL_TRUE, _vMat.getFloats());
	}
}

void RenderableEntity::bindUniforms()
{
	LightInfo linfo;
	MaterialInfo minfo;
	linfo.Lpos = Vector3(0,0,10);

	GLuint loc = glGetUniformLocation(shader->getProgram(), "Linfo.Lpos");
	if (loc != -1)
	{
		glUniform3f(loc, linfo.Lpos.x, linfo.Lpos.y, linfo.Lpos.z);
		loc = glGetUniformLocation(shader->getProgram(), "Linfo.La");
		glUniform3f(loc, linfo.La.x, linfo.La.y, linfo.La.z);
		loc = glGetUniformLocation(shader->getProgram(), "Linfo.Ld");
		glUniform3f(loc, linfo.Ld.x, linfo.Ld.y, linfo.Ld.z);
		loc = glGetUniformLocation(shader->getProgram(), "Linfo.Ls");
		glUniform3f(loc, linfo.Ls.x, linfo.Ls.y, linfo.Ls.z);
	}

	loc = glGetUniformLocation(shader->getProgram(), "Minfo.Ka");
	if (loc != -1)
	{
		glUniform3f(loc, minfo.Ka.x, minfo.Ka.y, minfo.Ka.z);
		loc = glGetUniformLocation(shader->getProgram(), "Minfo.Kd");
		glUniform3f(loc, minfo.Kd.x, minfo.Kd.y, minfo.Kd.z);
		loc = glGetUniformLocation(shader->getProgram(), "Minfo.Ks");
		glUniform3f(loc, minfo.Ks.x, minfo.Ks.y, minfo.Ks.z);
		loc = glGetUniformLocation(shader->getProgram(), "Minfo.shine");
		glUniform1i(loc, minfo.shine);
	}
		
}

void RenderableEntity::render(Matrix4& _vMat, Matrix4& _mvMat, Matrix4& _mvpMat)
{
	glUseProgram(shader->getProgram());
	bindMatrices(_vMat, _mvMat, _mvpMat);
	bindUniforms();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, shape->getNumInds(), GL_UNSIGNED_INT, 0);
}