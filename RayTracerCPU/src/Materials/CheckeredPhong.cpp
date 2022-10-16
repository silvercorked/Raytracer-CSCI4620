
#include "Materials/CheckeredPhong.h"

#include <cmath>
#include <algorithm>
#include <iostream>

using namespace RayTracerSpace;

CheckeredPhong::CheckeredPhong() :
	Material() {
}
CheckeredPhong::CheckeredPhong(Vector3 color) :
	Material(color) {
	this->color = Material::color;
}
CheckeredPhong::~CheckeredPhong() {}
Vector3* CheckeredPhong::shade(Vector3 fromDir, Vector3 pos, Vector3 normal, DirectionalLight dLight /*, std::vector<Mesh>* meshes, int remainingCasts */) {
	Vector3 lightDir = dLight.directionToLight;
	/* TBD */
	return &lightDir;
}
