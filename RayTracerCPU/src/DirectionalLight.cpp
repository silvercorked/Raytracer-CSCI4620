#include "DirectionalLight.h"

using namespace RayTracerSpace;

DirectionalLight::DirectionalLight() {
	this->directionToLight = Vector3();
	this->intensity = 1.0;
}

DirectionalLight::DirectionalLight(Vector3 directionToLight, double intensity) {
	this->directionToLight = directionToLight;
	this->intensity = intensity;
}

DirectionalLight DirectionalLight::normalize() {
	this->directionToLight.normalize();
	return *this;
}

DirectionalLight::~DirectionalLight() {}
