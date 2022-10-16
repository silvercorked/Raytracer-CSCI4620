
#include "includes/Geometry/Plane.h"
#include <iostream>

using namespace RayTracerSpace;
using namespace std;

Plane::Plane() {
	this->ABC = Vector3();
	this->D = 1.0;
}

Plane::Plane(Vector3 ABC, float D) {
	this->ABC = ABC;
	this->D = D;
}

Plane::Plane(Vector3 a, Vector3 b, Vector3 c) {
	Vector3* crossProduct = Vector3::minus(a, b);
	Vector3* cb = Vector3::minus(c, b);
	crossProduct->cross(*cb).normalize();
	this->ABC = Vector3(crossProduct->X, crossProduct->Y, crossProduct->Z);
	this->D = -this->ABC.dot(a);
	free(cb); free(crossProduct);
}

Intersection Plane::intersect(Ray ray, float closestDistance) {
	float num = (-this->D) - Vector3::dot(this->ABC, ray.origin);
	float den = Vector3::dot(this->ABC, ray.direction);
	return Intersection(num / den, this->ABC);
}

float Plane::offset(Vector3 collision) {
	return Vector3::dot(this->ABC, collision) + this->D;
}

Plane::~Plane() {}
