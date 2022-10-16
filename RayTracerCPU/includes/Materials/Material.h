
#ifndef MATERIAL_H
#define MATERIAL_H

#include "includes/Vector3.h"
#include "includes/DirectionalLight.h"

namespace RayTracerSpace {
	class Material {
	public:
		Vector3 color;
		Material();
		Material(Vector3);
		~Material();
		virtual Vector3* shade(Vector3, Vector3, Vector3, DirectionalLight) = 0;
	};
}
#endif