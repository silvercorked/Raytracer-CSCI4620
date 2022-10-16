
#ifndef PHONGMATERIAL_H
#define PHONGMATERIAL_H

#include "includes/Materials/Material.h"

namespace RayTracerSpace {
	class PhongMaterial : public Material {
	public:
		Vector3 color;
		Vector3 finalColor;
		PhongMaterial();
		PhongMaterial(Vector3);
		~PhongMaterial();
		Vector3* shade(Vector3, Vector3, Vector3, DirectionalLight);
	};
}
#endif