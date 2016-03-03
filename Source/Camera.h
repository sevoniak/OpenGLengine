#pragma once
#include "MathHelper.h"

class Camera
{
private:
	Vector3 position;
	Quaternion orientation;
	Vector3 fwdDirection;
	Vector3 upDirection;
	Matrix4 viewMatrix;

public:
	Camera(void);
	Camera (Vector3 pos, Vector3 fwd, Vector3 up);
	~Camera(void);

	void moveForward(float);
	void strafe(float);
	void crane(float);
	void roll(float);
	void pitch(float);
	void yaw(float);

	void moveToAbsolutePos(Vector3 pos);
	void pointToAbsoluteDir(Vector3 dir);

	Matrix4 getViewMatrix();
};

