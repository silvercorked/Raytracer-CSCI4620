
#ifndef CHECKEREDPHONG_H
#define CHECKEREDPHONG_H

#include "includes/Materials/Material.h"

namespace RayTracerSpace {
	class CheckeredPhong : public Material {
	public:
		Vector3 color;
		Vector3 finalColor;
		CheckeredPhong();
		CheckeredPhong(Vector3);
		~CheckeredPhong();
		Vector3* shade(Vector3, Vector3, Vector3, DirectionalLight);
	};
}
#endif
