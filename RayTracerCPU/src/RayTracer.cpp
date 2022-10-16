
#include "RayTracer.h"
#include <limits>
#include <chrono>

using namespace RayTracerSpace;

RayTracer::RayTracer() {
	this->lights = std::vector<DirectionalLight>();
	this->camera = Camera();
	this->meshes = std::vector<Mesh>();
	this->colors = std::vector<std::vector<Vector3>>();
}

RayTracer::RayTracer(std::vector<DirectionalLight> lights, Camera camera, std::vector<Mesh> meshes) {
	this->lights = lights;
	this->camera = camera;
	this->meshes = meshes;
	this->colors = std::vector<std::vector<Vector3>>();
}

RayTracer::~RayTracer() {}

bool RayTracer::render(cv::Mat* image) {
	//cv::Mat image(width, height, CV_8UC3);
	this->colors = std::vector<std::vector<Vector3>>(image->cols, std::vector<Vector3>(image->rows, Vector3()));
	std::cout << "Beginning Render" << std::endl << std::endl;
	std::cout << "  Rendering... 0%" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	for (int y = 0; y < image->rows; y++) {
		for (int x = 0; x < image->cols; x++) {
			this->colors[x][y] = Vector3(0, 0, 0); // default

			int samples = 16;

			Vector3* origin = &this->camera.origin;
			Vector3* lookAt = &this->camera.lookAt;
			Vector3* lookUp = &this->camera.upDirection;
			Vector3* lookDir = Vector3::minus(*lookAt, *origin);
			lookDir->normalize();
			Vector3* lookRight = Vector3::cross(*lookUp, *lookDir);
			lookRight->normalize();

			float percentX = x / (float) image->cols;
			float percentY = y / (float) image->rows;
			float scaleX = (percentX * 2) - 1;
			float scaleY = ((percentY * 2) - 1) * -1; // invert, math and screens are opposite
			
			float oppLength = (float)tan(this->camera.halfWidth);
			Vector3* lookRightSscaleX = Vector3::scale(*lookRight, scaleX);
			Vector3* lookUpSscaleY = Vector3::scale(*lookUp, scaleY);
			Vector3* lookAtPlookRightSscaleX = Vector3::plus(*lookAt, *lookRightSscaleX);
			Vector3* viewingPlanePoint = Vector3::plus(*lookAtPlookRightSscaleX, *lookUpSscaleY);
			free(lookRightSscaleX); free(lookUpSscaleY); free(lookAtPlookRightSscaleX);
			float pixelWidth = 2 * lookRight->length() / image->cols;
			for (int s = 0; s < samples; s++) {
				Vector3* direction = Vector3::minus(*viewingPlanePoint, *origin);
				direction->normalize();
				float jitterX = (randu<float>() * 2 - 1) * (0.1f * pixelWidth);
				float jitterY = (randu<float>() * 2 - 1) * (0.1f * pixelWidth);
				float jitterZ = (randu<float>() * 2 - 1) * (0.1f * pixelWidth);
				// create jitter values for anti-aliasing
				Vector3* jitter = new Vector3(jitterX, jitterY, jitterZ);
				direction->plus(*jitter).normalize();
				free(jitter);

				Ray ray = Ray(*origin, *direction);
				/*Intersection intersection = ray.shootRay(&this->meshes);
				if (intersection.mesh.geometry != nullptr) {
					Vector3* rayAtIntersection = ray.direction.scale(intersection.t);
					Vector3* collisionPosition = ray.origin.plus(rayAtIntersection);
					Vector3* rayAtCollision = ray.origin.minus(collisionPosition);
					Vector3* fromDir = rayAtCollision->normalize();
					Vector3* closestColor = intersection.mesh.shader->shade(
						*fromDir,
						*collisionPosition,
						intersection.normal,
						lights[0],
						*this,
						2
					);
					Vector3* newColor = colors[x][y].plus(closestColor);
					colors[x][y] = *newColor;
				}*/
			}
			colors[x][y].scale(1 / (float)samples);
		}
		end = std::chrono::high_resolution_clock::now();
		std::cout << "\x1b[1A";
		std::cout
			<< std::fixed
			<< std::setprecision(5)
			<< "  Rending... "
			<< (float) ((y + 1) / (float) image->rows) * 100
			<< "% "
			<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0L
			<< "ms last pixel"
		<< std::endl;
		start = end;
	}
	std::cout << "Render Complete" << std::endl;
	return true;
}

bool RayTracer::save(cv::Mat* image, std::string outputFilename) {
	std::cout << "Saving Image" << std::endl;
	for (int y = 0; y < image->cols; y++) {
		for (int x = 0; x < image->rows; x++) {
			Vector3 color = this->colors[x][y];
			Vec3b* colorInType = new Vec3b(
				(uchar)(color.X * 255),
				(uchar)(color.Y * 255),
				(uchar)(color.Z * 255)
			);
			/*if (color.lengthSquared() != 0)
				std::cout
					<< "color[" << x << "][" << y
					<< "] X: " << color.X << " Y: " << color.Y
					<< " Z: " << color.Z
					<< " realColor X: " << colorInType->row(0)
					<< " Y: " << colorInType->row(1)
					<< " Z: " << colorInType->row(2)
				<< std::endl;*/
			image->at<Vec3b>(Point(x, y)) = *colorInType;
		}
	}
	return cv::imwrite("output\\" + outputFilename + ".png", *image);
}
