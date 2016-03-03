#pragma once
#include "Defs.h"
#include "Texture.h"
#include "Shape.h"
#include "Shader.h"

class RenderableEntity
{
private:
	Vector4* colors;
	Vector2* texCoords;
	int numColors;
	int numTexCoords;
	Texture* texture;
	Shape* shape;
	Shader* shader;
	GLuint cao;
	GLuint tao;
	GLuint vao;

	void initVAO();
	void generateBuffers();
	void bindBuffers();
	void bindShape();
	void bindMatrices(Matrix4&, Matrix4&, Matrix4&);
	void bindUniforms();

public:
	RenderableEntity(void);
	RenderableEntity(Shape*, Shader*);
	~RenderableEntity(void);
	
	void setColorless();
	void setColors(Vector4*, int);
	void setTexture(Texture*, Vector2*, int);
	void render(Matrix4& _vMat, Matrix4& _mvMat, Matrix4& _mvpMat);
};

