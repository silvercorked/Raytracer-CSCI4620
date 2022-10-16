
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "includes/Vector3.h"
#include "includes/Geometry/Geometry.h"

namespace RayTracerSpace {
	class Triangle: public Geometry {
		private:
			Vector3 one;
			Vector3 two;
			Vector3 three;
		public:
			Triangle();
			Triangle(Vector3, Vector3, Vector3);
			
			Vector3 getOne();
			Vector3 getTwo();
			Vector3 getThree();
			void setOne(Vector3);
			void setTwo(Vector3);
			void setThree(Vector3);
			Intersection intersect(Ray, float) override;
			~Triangle();
	};
}
#endif