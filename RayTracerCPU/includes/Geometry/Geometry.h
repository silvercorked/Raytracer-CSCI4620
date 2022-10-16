
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "includes/Vector3.h"
#include "includes/Ray.h"
#include "includes/Intersection.h"

namespace RayTracerSpace {
	class Geometry {
	public:
		Geometry();
		~Geometry();
		virtual Intersection intersect(Ray, float) = 0;
	};
}
#endif