
#ifndef MESH_H
#define MESH_H

#include "includes/Materials/Material.h"
#include "includes/Geometry/Geometry.h"

namespace RayTracerSpace {
	class Mesh {
	public:
		Geometry* geometry;
		Material* shader;
		Mesh();
		Mesh(Geometry*, Material*);
		~Mesh();
	};
}
#endif