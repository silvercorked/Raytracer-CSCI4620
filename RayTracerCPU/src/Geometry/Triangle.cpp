
#include "Geometry/Triangle.h"
#include "Geometry/Plane.h"
#include <iostream>

using namespace RayTracerSpace;

using namespace std;

Triangle::Triangle() {
	this->one = Vector3();
	this->two = Vector3();
	this->three = Vector3();
}

Triangle::Triangle(Vector3 one, Vector3 two, Vector3 three) {
	this->one = one;
	this->two = two;
	this->three = three;
}

Vector3 Triangle::getOne() {
	return this->one;
}

Vector3 Triangle::getTwo() {
	return this->two;
}

Vector3 Triangle::getThree() {
	return this->three;
}

void Triangle::setOne(Vector3 one) {
	this->one = one;
}

void Triangle::setTwo(Vector3 two) {
	this->two = two;
}

void Triangle::setThree(Vector3 three) {
	this->three = three;
}

Intersection Triangle::intersect(Ray ray, float closestDistance) {
	Plane plane = Plane(this->one, this->two, this->three);

	Intersection planeIntersection = plane.intersect(ray, closestDistance);
	if (planeIntersection.t > closestDistance) return Intersection(-1, Vector3());
	Vector3* dirSplaneInterT = Vector3::scale(ray.direction, planeIntersection.t);
	Vector3* collision = Vector3::plus(ray.origin, *dirSplaneInterT);
	Vector3 normal = planeIntersection.normal;

	Vector3* onePnormal = Vector3::plus(this->one, normal);
	Vector3* twoPnormal = Vector3::plus(this->two, normal);
	Vector3* threePnormal = Vector3::plus(this->three, normal);

	Plane plane1 = Plane(this->two, this->one, *twoPnormal);
	Plane plane2 = Plane(this->three, this->two, *threePnormal);
	Plane plane3 = Plane(this->one, this->three, *onePnormal);

	float distance1 = plane1.offset(*collision);
	float distance2 = plane2.offset(*collision);
	float distance3 = plane3.offset(*collision);

	free(collision); free(onePnormal); free(twoPnormal); free(threePnormal);

	if (distance1 >= 0 && distance2 >= 0 && distance3 >= 0) { // collision
		return planeIntersection;
	}
	return Intersection(-1, Vector3());
}

Triangle::~Triangle() {}
