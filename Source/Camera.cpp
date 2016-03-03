#include "Camera.h"


Camera::Camera(void)
{
	position = Vector3(0,0,8);
	orientation.identity();
	upDirection = Vector3(0,1,0);
	fwdDirection = Vector3(0,0,-1);
}

Camera::Camera(Vector3 pos, Vector3 dir, Vector3 up):
	position(pos), fwdDirection(dir), upDirection(up)
{
}

Camera::~Camera(void)
{
}

void Camera::moveForward(float dist)
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	fwd.normalize();
	position += dist * fwd;
}

void Camera::strafe(float dist)
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	Vector3 up = upDirection * orientation.toMatrix4();
	Vector3 side;
	side = side.cross(fwd, up);
	side.normalize();
	position += dist * side;
}

void Camera::crane(float dist)
{
	Vector3 up = upDirection * orientation.toMatrix4();
	up.normalize();
	position += dist * up;
}

void Camera::roll(float angle)
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	Quaternion delta;
	delta.fromAxisAngle(fwd, Math::radiansToDegrees(angle));
	orientation = orientation * delta;
}

void Camera::pitch(float angle)
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	Vector3 up = upDirection * orientation.toMatrix4();
	Vector3 side;
	side = side.cross(fwd, up);
	side.normalize();

	Quaternion delta;
	delta.fromAxisAngle(side, Math::radiansToDegrees(angle));
	orientation *= delta;
}

void Camera::yaw(float angle)
{
	Vector3 up = upDirection * orientation.toMatrix4();
	Quaternion delta;
	delta.fromAxisAngle(up, Math::radiansToDegrees(angle));
	orientation *= delta;
}

void Camera::moveToAbsolutePos(Vector3 pos)
{
	position = pos;
}

void Camera::pointToAbsoluteDir(Vector3 dir)
{
	Vector3 up = upDirection * orientation.toMatrix4();
	Matrix4 mat = orientationMatrix(dir, up);
	orientation.fromMatrix(mat);
}

Matrix4 Camera::getViewMatrix()
{
	Vector3 fwd = fwdDirection * orientation.toMatrix4();
	Vector3 up = upDirection * orientation.toMatrix4();
	viewMatrix = createViewMatrix(position, fwd, up);
	return viewMatrix;
}
