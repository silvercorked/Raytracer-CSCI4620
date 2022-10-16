
#include "Intersection.h"

using namespace RayTracerSpace;

Intersection::Intersection() {
	this->t = 1.0;
	this->normal = Vector3();
}

Intersection::Intersection(float t, Vector3 normal) {
	this->t = t;
	this->normal = normal;
}

Intersection::~Intersection() {}
