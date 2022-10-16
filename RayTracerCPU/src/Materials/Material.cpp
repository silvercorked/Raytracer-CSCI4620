
#include "Materials/Material.h"

using namespace RayTracerSpace;

Material::Material() {
	this->color = Vector3();
}

Material::Material(Vector3 color) {
	this->color = color;
}

Material::~Material() {}
