
#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "includes/Vector3.h"

namespace RayTracerSpace {
	class DirectionalLight {
	public:
		Vector3 directionToLight;
		double intensity;
		DirectionalLight();
		DirectionalLight(Vector3, double);
		~DirectionalLight();
		DirectionalLight normalize();
	};
}
#endif