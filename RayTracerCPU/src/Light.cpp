
#include "Light.h"

using namespace RayTracerSpace;

Light::Light() {
	this->direction = Vector3();
	this->color = Vector3();
}

Light::Light(Vector3 dir, Vector3 color) {
	this->direction = dir;
	this->color = color;
}

Light::~Light() {}
