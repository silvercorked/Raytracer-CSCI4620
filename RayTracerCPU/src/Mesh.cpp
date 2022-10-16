
#include "Mesh.h"
#include "Geometry/Sphere.h"

using namespace RayTracerSpace;

Mesh::Mesh() {
	Sphere temp = Sphere(); // dummy sphere as geometry
	this->geometry = &(temp);
	this->shader = nullptr;
}

Mesh::Mesh(Geometry* geometry, Material* shader) {
	this->geometry = geometry;
	this->shader = shader;
}

Mesh::~Mesh() {}
