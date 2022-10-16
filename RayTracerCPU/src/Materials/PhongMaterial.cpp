
#include "Materials/PhongMaterial.h"
#include "Ray.h"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace RayTracerSpace;

PhongMaterial::PhongMaterial() {
	this->color = Vector3();
}
PhongMaterial::PhongMaterial(Vector3 color) {
	this->color = color;
}
PhongMaterial::~PhongMaterial() {}
Vector3* PhongMaterial::shade(Vector3 fromDir, Vector3 pos, Vector3 normal, DirectionalLight dLight /*, std::vector<Mesh>* meshes, int remainingCasts */) {
	Vector3 lightDir = dLight.directionToLight;
	Vector3* lightDirS = Vector3::scale(lightDir, 0.1f);
	Vector3* posPlightDir = Vector3::plus(pos, *lightDirS);
	Ray shadowRay = Ray(*posPlightDir, lightDir);
	free(lightDirS); free(posPlightDir);
	//Intersection shadowIntersection = shadowRay.shootRay(meshes);
	bool inShadow = false;
	//if (shadowIntersection.t != -1) inShadow = true;
	if (!inShadow) {
		Vector3 ambient = Vector3(0.1f, 0.1f, 0.1f);
		Vector3* normal_p = &normal;
		if (normal.dot(fromDir) < 0) {
			normal_p = Vector3::scale(normal, -1);
		}
		Vector3* normalNormed_p = Vector3::normalize(*normal_p);
		Vector3* lightdirNormed_p = Vector3::normalize(dLight.directionToLight);
		
		float diffuseStrength = std::max(0.0f, normalNormed_p->dot(*lightdirNormed_p));
		//std::cout << " normal x: " << normal.X << " y: " << normal.Y << " z: " << normal.Z << "   diffStr Max "<< normal.normalize().dot(dLight.directionToLight.normalize()) << std::endl;
		Vector3* diffuse = Vector3::scale(this->color, diffuseStrength);
		free(normalNormed_p); free(lightdirNormed_p);

		//std::cout << "   diffuse x: " << diffuse.X << " y: " << diffuse.Y << " z: " << diffuse.Z << "   diffStr " << diffuseStrength << std::endl;
		Vector3* reflection = Vector3::reflect(dLight.directionToLight, *normal_p);
		float specularStrength = (float) std::pow(std::max(0.0f, reflection->dot(fromDir)), 4);
		Vector3* ones = new Vector3(1.0f, 1.0f, 1.0f);
		Vector3* specular = Vector3::scale(*ones, specularStrength);
		free(normal_p); free(reflection); free(ones);
		//std::cout << "  final color x: " << finalColor.X << " y: " << finalColor.Y << " z: " << finalColor.Z << std::endl;

		this->finalColor = ambient;
		this->finalColor.plus(*diffuse).plus(*specular);
	}
	this->finalColor.clamp(0, 1);
	return &this->finalColor;
}
