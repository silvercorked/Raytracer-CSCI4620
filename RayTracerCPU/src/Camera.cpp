
#include "Camera.h"

using namespace RayTracerSpace;

Camera::Camera() {
	this->origin = Vector3();
	this->lookAt = Vector3();
	this->upDirection = Vector3();
	this->halfWidth = 1.0;
}

Camera::Camera(Vector3 origin, Vector3 lookAt, Vector3 upDirection, double halfWidth) {
	this->origin = origin;
	this->lookAt = lookAt;
	this->upDirection = upDirection;
	this->halfWidth = halfWidth;
}

Camera::~Camera() {}
