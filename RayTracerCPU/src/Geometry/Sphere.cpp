
#include "Sphere.h"
//#include <iostream>

using namespace RayTracerSpace;

Sphere::Sphere() {
	this->center = Vector3();
	this->radius = 1.0;
}

Sphere::Sphere(Vector3 center, float radius) {
	this->center = center;
	this->radius = radius;
}

Intersection Sphere::intersect(Ray ray, float closestDistance) {
	Vector3* oc = Vector3::minus(ray.origin, center);
	float A = Vector3::dot(ray.direction, ray.direction);
	float B = 2 * Vector3::dot(ray.direction, *oc);
	float C = Vector3::dot(*oc, *oc) - radius * radius;
	float inSqrt = B * B - 4 * A * C;
	if (inSqrt < 0) {
		return Intersection(-1, Vector3());
	}
	float num1 = -1 * B - (float) sqrt(inSqrt);
	float num2 = -1 * B + (float) sqrt(inSqrt);
	float den = 2 * A;
	float t1 = num1 / den;
	float t2 = num2 / den;
	float t;
	//std::cout << "t1: " << t1 << " t2: " << t2 << std::endl;
	if (t1 > 0 && t1 < t2) t = t1;
	else if (t1 < 0 && t2 > 0) t = t2;
	else return Intersection(-1, Vector3());
	Vector3* dirSscaleT = Vector3::scale(ray.direction, t);
	Vector3* collisionPoint = Vector3::plus(ray.origin, *dirSscaleT);
	collisionPoint->minus(center).normalize();
	
	free(oc);
	return Intersection(t, *collisionPoint);
}

Sphere::~Sphere() {}
