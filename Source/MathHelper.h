#pragma once

#include "Mathlib.h"

inline Matrix4 scaleMatrix(Vector3 scale)
{
	Matrix4 scaleMat = Matrix4::IDENTITY;
	scaleMat[0][0] = scale.x;
	scaleMat[1][1] = scale.y;
	scaleMat[2][2] = scale.z;

	return scaleMat;
}

inline Matrix4 translationMatrix(Vector3 vector)
{
	Matrix4 translation = Matrix4::IDENTITY;
	translation[0][3] = vector.x;
	translation[1][3] = vector.y;
	translation[2][3] = vector.z;

	return translation;
}

inline Matrix4 orientationMatrix(Vector3 forward, Vector3 upVector)
{
	Matrix4 orientation = Matrix4::IDENTITY;
	Vector3 right, up;

	forward.normalize();

	right = Vector3::cross(forward, upVector);
	right.normalize();

	orientation = Matrix4(right.x, right.y, right.z, 0,
		upVector.x, upVector.y, upVector.z, 0,
		-forward.x, -forward.y, -forward.z, 0,
		0, 0, 0, 1);

	return orientation;
}

inline Matrix4 createOrthographicProjectionMatrix(float width, float height, float nearPlane, float farPlane)
{
	Matrix4 projectionMatrix;
	projectionMatrix = Matrix4::IDENTITY;
	
	projectionMatrix[0][0] = 2 / width;
	projectionMatrix[1][1] = 2 / height;
	projectionMatrix[2][2] = 2 / (farPlane-nearPlane);
	projectionMatrix[2][3] = -(nearPlane + farPlane) / (nearPlane - farPlane);
	
	return projectionMatrix;
}

inline Matrix4 createPerspectiveProjectionMatrix(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	Matrix4 projectionMatrix;
	float cot = 1.0f / tan(Math::degreesToRadians(fieldOfView) / 2);

	projectionMatrix = Matrix4::IDENTITY;
	projectionMatrix[0][0] = cot / aspectRatio;
	projectionMatrix[1][1] = cot;
	projectionMatrix[2][2] = (nearPlane + farPlane) / (nearPlane - farPlane);
	projectionMatrix[2][3] = (2 * nearPlane*farPlane) / (nearPlane - farPlane);
	projectionMatrix[3][2] = -1;
	projectionMatrix[3][3] = 0;

	return projectionMatrix;
}

inline Matrix4 createViewMatrix(Vector3 position, Vector3 forward, Vector3 upVector)
{
	Matrix4 viewMatrix;
	Matrix4 orientation = orientationMatrix(forward,upVector);
	Matrix4 translation = translationMatrix(-position);

	viewMatrix = orientation *translation;

	return viewMatrix;
}