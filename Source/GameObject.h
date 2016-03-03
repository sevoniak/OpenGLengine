#pragma once
#include "Defs.h"
#include "RenderableEntity.h"
#include "MathHelper.h"
#include <vector>
using std::vector;

class GameObject
{
private:
	Matrix4 worldMat;
	Matrix4 scaleMat;
	Vector3 position;
	Quaternion orientation;
	RenderableEntity* entity;
	vector<GameObject*> children;
	Vector3 fwdDirection;
	Vector3 upDirection;

public:
	GameObject(void);
	GameObject(Shape*, Shader*, Vector4*);
	~GameObject(void);

	void render(Matrix4&, Matrix4&);
	void render(Matrix4&, Matrix4&, Matrix4&);

	void translateAbs(Vector3);
	void translateRel(Vector3);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
	void rotateAxis(Vector3, float);
	void scale(Vector3);
};

