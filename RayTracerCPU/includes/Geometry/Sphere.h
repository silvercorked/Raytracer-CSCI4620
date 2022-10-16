
#ifndef SPHERE_H
#define SPHERE_H

#include "includes/Vector3.h"
#include "includes/Geometry/Geometry.h"

namespace RayTracerSpace {
	class Sphere: public Geometry {
	private:
		Vector3 center;
		float radius;
	public:
		Sphere();
		Sphere(Vector3, float);
		~Sphere();
		Intersection intersect(Ray, float) override;
	};
}
#endif