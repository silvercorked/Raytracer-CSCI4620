
#ifndef CAMERA_H
#define CAMERA_H

#include "includes/Vector3.h"

namespace RayTracerSpace {
	class Camera {
	public:
		Vector3 origin;
		Vector3 lookAt;
		Vector3 upDirection;
		double halfWidth;

		Camera();
		Camera(Vector3, Vector3, Vector3, double);
		~Camera();
	};
}
#endif