#include "GameObject.h"


GameObject::GameObject(void)
{
	worldMat.identity();
	scaleMat.identity();
	position.set(0.0f, 0.0f, 0.0f);
	orientation.identity();
	entity = 0;
	fwdDirection = Vector3(0,0,-1);
	upDirection = Vector3(0,1,0);
}

GameObject::GameObject(Shape* _shape, Shader* _shader, Vector4* _cols)
{
	worldMat.identity();
	scaleMat.identity();
	position.set(0.0f, 0.0f, 0.0f);
	orientation.identity();
	entity = new RenderableEntity(_shape, _shader);
	if (_cols)
		entity->setColors(_cols, _shape->getNumVerts());
	else
		entity->setColorless();
	fwdDirection = Vector3(0,0,-1);
	upDirection = Vector3(0,1,0);
}


GameObject::~GameObject(void)
{
	if (entity) delete entity;
	for (unsigned int i = 0; i < children.size(); i++)
		delete children[i];
}

void GameObject::render(Matrix4& _viewMat, Matrix4& _projMat)
{
	//proj * view * TORSI * vec
	worldMat = translationMatrix(position) * orientation.toMatrix4();
	Matrix4 mvMat = _viewMat * worldMat * scaleMat;
	Matrix4 mvpMat = _projMat * mvMat;
	
	entity->render(_viewMat, mvMat, mvpMat);
	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->render(_viewMat, _projMat, worldMat);
}

void GameObject::render(Matrix4& _viewMat, Matrix4& _projMat, Matrix4& _parentMat)
{
	//proj * view * parent * TORSI * vec
	worldMat = _parentMat * translationMatrix(position) * orientation.toMatrix4();
	Matrix4 mvMat = _viewMat * worldMat * scaleMat;
	Matrix4 mvpMat = _projMat * mvMat;
	
	entity->render(_viewMat, mvMat, mvpMat);
	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->render(_viewMat, _projMat, worldMat);
}

void GameObject::translateAbs(Vector3 _vec)
{
	position += _vec;
}

void GameObject::translateRel(Vector3 _vec)
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	Vector3 up = upDirection * orientation.toMatrix4();
	Vector3 side;
	side = side.cross(fwd, up);
	fwd.normalize();
	up.normalize();
	side.normalize();

	position += (_vec.x * side) + (_vec.y * up) + (_vec.z * fwd);
}

void GameObject::rotateX(float _angle)
{
	Quaternion delta;
	delta.fromAxisAngle(Vector3(1,0,0), _angle);
	orientation = delta * orientation;
}

void GameObject::rotateY(float _angle)
{
	Quaternion delta;
	delta.fromAxisAngle(Vector3(0,1,0), _angle);
	orientation = delta * orientation;
}

void GameObject::rotateZ(float _angle)
{
	Quaternion delta;
	delta.fromAxisAngle(Vector3(0,0,1), _angle);
	orientation = delta * orientation;
}

void GameObject::rotateAxis(Vector3 _vec, float _angle)
{
	Quaternion delta;
	_vec.normalize();
	delta.fromAxisAngle(_vec, _angle);
	orientation = delta * orientation;
}

void GameObject::scale(Vector3 _vec)
{
	Matrix4 delta = scaleMatrix(_vec);
	scaleMat *= delta;
}
