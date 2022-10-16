
#include "Ray.h"

using namespace RayTracerSpace;

Ray::Ray() {
	this->origin = Vector3();
	this->direction = Vector3();
}

Ray::Ray(Vector3 origin, Vector3 direction) {
	this->origin = origin;
	this->direction = direction;
}

/*
Intersection Ray::shootRay(std::vector<Mesh>* meshes) {
	float closestDistance = std::numeric_limits<float>::max();
	Vector3* closestColor = NULL;
	Vector3* closestNormal = NULL;
	int closestMesh = -1;
	for (int i = 0; i < meshes->size(); i++) {
		Mesh mesh = meshes->at(i);
		Material* shader = mesh.shader;
		// cast ray
		Intersection tn = mesh.geometry->intersect(*this, closestDistance);
		if (tn.t <= 0) continue;
		if (tn.t < closestDistance) {
			closestMesh = i;
			closestDistance = tn.t;
			closestNormal = &tn.normal;
			tn.mesh = mesh;
			// do shading
			
			//Vector3* rayScaledToIntersection = ray.direction.scale(tn.t);
			//Vector3* closestPoint = ray.origin.plus(rayScaledToIntersection);
			//Vector3* rayNearclosestPoint = ray.origin.minus(closestPoint);
			//Vector3* fromDirection = rayNearclosestPoint->normalize();
			
			// the next line will shoot more rays to gather more reflections
			// closestColor = shader->shade(fromDirection, closestPoint, *closestNormal, lights[0]);
		}
	}
	if (closestMesh == -1) return Intersection();
	return Intersection(
		closestDistance,
		*closestNormal,
		(closestMesh == -1 ? Mesh() : meshes[closestMesh])
	);
}*/

Ray::~Ray() {}
