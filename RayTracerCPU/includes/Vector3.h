
#ifndef VECTOR3_H
#define VECTOR3_H

#include "includes/Vector2.h"

#include <cmath>
#include <algorithm>

typedef unsigned char uint8_t;

namespace RayTracerSpace {
	class Vector3 {
		public:
			float X;
			float Y;
			float Z;
			Vector3();
			Vector3(double, double, double);
			~Vector3();
			static Vector3* ZERO();
			static Vector3* ZEROW();
			static Vector3* plus(Vector3&, Vector3&);
			Vector3& plus(Vector3&);
			static Vector3* minus(Vector3&, Vector3&);
			Vector3& minus(Vector3&);
			static Vector3* negate(Vector3&);
			Vector3& negate();
			static Vector3* scale(Vector3&, float);
			Vector3& scale(float);
			static float length(Vector3&);
			float length() const;
			static float lengthSquared(Vector3&);
			float lengthSquared() const;
			static Vector3* normalize(Vector3&);
			Vector3& normalize();
			static float dot(Vector3&, Vector3&);
			float dot(Vector3&) const;
			static Vector3* cross(Vector3&, Vector3&);
			Vector3& cross(Vector3&);
			static bool equals(Vector3&, Vector3&);
			bool equals(Vector3&) const;
			static float absoluteDifference(Vector3&, Vector3&);
			float absoluteDifference(Vector3&) const;
			static bool nearlyEquals(Vector3&, Vector3&);
			bool nearlyEquals(Vector3&) const;
			static Vector3 fromVector2(Vector2);
			//float* asArray();
			float at(uint8_t) const;
			Vector3& setAt(uint8_t, float);
			float getW() const;
			void setW(float);
			static Vector3* clamp(Vector3&, float, float);
			Vector3& clamp(float, float);
			static Vector3* reflect(Vector3&, Vector3&);
			Vector3& reflect(Vector3&);
	};
}

#endif
