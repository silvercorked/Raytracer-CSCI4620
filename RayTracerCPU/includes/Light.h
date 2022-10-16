
#ifndef LIGHT_H
#define LIGHT_H

#include "includes/Vector3.h"

namespace RayTracerSpace {
	class Light {
	private:
		Vector3 direction;
		Vector3 color;
	public:
		Light();
		Light(Vector3, Vector3);
		~Light();
	};
}
#endif
