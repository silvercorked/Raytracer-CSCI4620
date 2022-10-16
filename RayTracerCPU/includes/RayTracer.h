
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "includes/DirectionalLight.h"
#include "includes/Camera.h"
#include "includes/Mesh.h"
#include "includes/Intersection.h"

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

using namespace cv;

namespace RayTracerSpace {
	class RayTracer {
		private:
			std::vector<DirectionalLight> lights;
			Camera camera;
			std::vector<Mesh> meshes;
			std::vector<std::vector<Vector3>> colors;
		public:
			RayTracer();
			RayTracer(std::vector<DirectionalLight>, Camera, std::vector<Mesh>);
			~RayTracer();
			bool render(cv::Mat*);
			Intersection shootRay(Ray);
			bool save(cv::Mat*, std::string);
	};
}
#endif