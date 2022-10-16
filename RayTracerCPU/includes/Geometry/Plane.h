
#ifndef PLANE_H
#define PLANE_H

#include "includes/Geometry/Geometry.h"
#include "includes/Vector3.h"

namespace RayTracerSpace {
	class Plane: public Geometry {
	public:
		Vector3 ABC;
		float D;
		Plane();
		Plane(Vector3, float);
		Plane(Vector3, Vector3, Vector3);
		~Plane();
		Intersection intersect(Ray, float) override;
		float offset(Vector3);
	};
}
#endif