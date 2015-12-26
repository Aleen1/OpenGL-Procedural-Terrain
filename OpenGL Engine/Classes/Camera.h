#pragma once

#include "Utils/Math/Matrix4.h"
#include "Transform.h"

enum Projection {Orthographic, Perspective};

class Camera {
private:
	static Camera* mainCamera;

	float aspectRatio, nearClip, farClip;
	// orthographic
	float orthographicSize;
	// perspective
	float fieldOfView;

	Projection projectionType;
	Matrix4 projectionMatrix;
	Transform* transform;

	void Zoom(float value);

public:
	static Camera* GetMainCamera();

	Camera(Projection projection, float size, float aspectRatio, float nearClip = 1.0f, float farClip = 100.0f);
	~Camera();
	Projection GetProjectionType();
	Matrix4 GetProjectionMatrix();
	Transform* GetTransform();

	void ZoomIn();
	void ZoomOut();

	void SetOrthographic(float size, float aspectRatio, float nearClip = 1.0f, float farClip = 100.0f);
	void SetPerspective(float fieldOfView, float aspectRatio, float nearClip = 1.0f, float farClip = 100.0f);
};