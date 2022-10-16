
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "includes/Vector3.h"

namespace RayTracerSpace {
	class Intersection {
	public:
		float t;
		Vector3 normal;
		Intersection();
		Intersection(float, Vector3);
		~Intersection();
	};
}
#endif