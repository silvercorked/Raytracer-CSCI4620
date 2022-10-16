
#ifndef RAY_H
#define RAY_H

#include "includes/Vector3.h"
#include "includes/Intersection.h"

namespace RayTracerSpace {
	class Ray {
	public:
		Vector3 origin;
		Vector3 direction;
		Ray();
		Ray(Vector3, Vector3);
		~Ray();
	};
}
#endif