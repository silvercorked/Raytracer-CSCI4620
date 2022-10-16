// RayTracerCPU.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "includes/RayTracer.h"
#include "includes/Geometry/Triangle.h"
#include "includes/Geometry/Plane.h"
#include "includes/Geometry/Sphere.h"
#include "includes/TokenizeOBJ.h"
#include "includes/Materials/PhongMaterial.h"

#define _USE_MATH_DEFINES // allows access to M_PI (PI in c++)
#include <math.h>
#include <filesystem>
#include <chrono>
#include <iostream>

using namespace RayTracerSpace;

bool tests(void);

int main() {
    auto fullStart = std::chrono::high_resolution_clock::now();
    std::cout << "starting tests" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    bool testsPassed = tests();
    auto end = std::chrono::high_resolution_clock::now();

    std::cout
        << "tests "
        << (testsPassed ? "passed!" : "failed!")
        << " in "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "microseconds"
    << std::endl;

    if (!testsPassed) return 1;

    std::string filename;
    std::cout << "Type filename (ignore extension as only .obj is accepted): ";
    std::getline(std::cin, filename);
    
    start = std::chrono::high_resolution_clock::now();
    TokenizeOBJ tokenizer = TokenizeOBJ(std::filesystem::current_path().string() + "\\objfiles\\" + filename + ".obj");
    bool res = tokenizer.tokenizeOBJ();
    end = std::chrono::high_resolution_clock::now();
    std::cout
        << (res ? " Successfully Parsed OBJ File" : "Failed to Parse OBJ File")
        << " in "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0L
        << "milliseconds"
    << std::endl;

    int width = 512;
    int height = 512;

    // Create geometry
    Vector3 pointOne = Vector3(0, 0, 0);
    Vector3 pointTwo = Vector3(1, 0, 0);
    Vector3 pointThree = Vector3(0, 1, 0);
    Triangle triangle = Triangle(pointOne, pointTwo, pointThree);

    Plane plane1 = Plane(Vector3(0, 0, -1), 1);
    Plane plane2 = Plane(Vector3(0, -1 / sqrt(2), -1 / sqrt(2)), 1);

    Sphere sphere1 = Sphere(Vector3(), 0.5f);

    //Material mat1 = Material(Vector3(0, 1, 0));
    //Material mat2 = Material(Vector3(1, 0, 0));
    //Material mat3 = Material(Vector3(0, 0, 1));
    
    PhongMaterial mat1 = PhongMaterial(Vector3(0, 0, 1));

    Mesh mesh1 = Mesh(&plane1, &mat1);
    Mesh mesh2 = Mesh(&plane2, &mat1);
    Mesh triangleMesh = Mesh(&triangle, &mat1);
    Mesh sphereMesh1 = Mesh(&sphere1, &mat1);
    
    //Mesh mesh3 = Mesh(&sphere1, mat3);

    /*for (const Faces f : tokenizer.getFaces()) {
        std::string faceStr = "face:";
        for (const Vector3 v : f.vertices) {
            faceStr.append("\n    1:");
            faceStr.append(std::to_string(v.at(0)));
            faceStr.append(" 2:");
            faceStr.append(std::to_string(v.at(1)));
            faceStr.append(" 3:");
            faceStr.append(std::to_string(v.at(2)));
        }
        std::cout << faceStr << std::endl;
    }*/
    
    std::vector<Triangle*> triangles = std::vector<Triangle*>();
    std::vector<Mesh> meshes = std::vector<Mesh>();
    for (const Faces f : tokenizer.getFaces()) {
        if (f.vertices.size() == 3) {
            triangles.push_back(new Triangle(f.vertices.at(0), f.vertices.at(1), f.vertices.at(2)));
            Triangle* t = triangles.back();
            meshes.push_back(Mesh(t, &mat1));
        }
        else {
            std::cerr << "ERROR, Invalid triangle" << std::endl;
        }
    }

    /*for (const Mesh m : meshes) {
        Triangle* t = (Triangle*) m.geometry;
        std::string faceStr = "triangles:";
        for (int i = 0; i < 3; i++) {
            Vector3 v = (i == 0
                ? t->getOne()
                : (i == 1
                    ? t->getTwo()
                    : t->getThree()));
            faceStr.append("\n    1:");
            faceStr.append(std::to_string(v.at(0)));
            faceStr.append(" 2:");
            faceStr.append(std::to_string(v.at(1)));
            faceStr.append(" 3:");
            faceStr.append(std::to_string(v.at(2)));
        }
        std::cout << faceStr << std::endl;
    }*/
    
    // Camera Points
    Vector3 cameraOrigin = Vector3(0, 0, -1);
    Vector3 cameraLookAt = Vector3(0, 0, 0);
    Vector3 cameraLookUp = Vector3(0, 1, 0);
    double halfWidth = M_PI / 4;
    Camera camera = Camera(cameraOrigin, cameraLookAt, cameraLookUp, halfWidth);

    // Light Points
    Vector3* directionToLight = new Vector3(1, 1, -1);
    directionToLight->normalize();
    DirectionalLight light = DirectionalLight(*directionToLight, 1);

    RayTracer level = RayTracer(
        std::vector<DirectionalLight> { light },
        camera,
        //std::vector<Mesh> { triangleMesh }
        meshes //std::vector<Mesh> { mesh1, mesh2, sphereMesh1  }
    );
    start = std::chrono::high_resolution_clock::now();
    cv::Mat image(width, height, CV_8UC3);
    bool result = level.render(&image);
    result = level.save(&image, filename + "Output");
    end = std::chrono::high_resolution_clock::now();

    std::cout
        << (result ? "Image Successfully Saved" : "ERROR: Image Not Saved")
        << " in "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0L
        << "seconds"
    << std::endl;

    std::cout
        << "Program ~Runtime: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - fullStart
        ).count() / 1000.0L
        << "seconds"
    << std::endl;
}

bool tests() {
    Vector3* v0 = new Vector3(0,0,0);
    Vector3* v1 = new Vector3(1, 1, 1);
    Vector3* v2 = new Vector3(2, 2, 2);
    Vector3* v3 = new Vector3(-3, 2, -1);

    float dot0 = v0->dot(*v1);
    if (dot0 != 0) {
        std::cout << "Test Error: Dot0" << std::endl;
        return false;
    }
    float dot1 = v1->dot(*v2);
    if (dot1 != 6) {
        std::cout << "Test Error: Dot1" << std::endl;
        return false;
    }

    Vector3* n1 = Vector3::normalize(*v1);
    Vector3* n1Test = new Vector3(1 / sqrt(3), 1 / sqrt(3), 1 / sqrt(3));
    if (!n1->nearlyEquals(*n1Test)) {
        std::cout << "Test Error: normal1" << std::endl;
        return false;
    }
    free(n1);
    Vector3* n2 = Vector3::normalize(*v2);
    if (!n2->nearlyEquals(*n1Test)) {
        std::cout << "Test Error: normal2" << std::endl;
        return false;
    }
    free(n1Test);
    if (v0->length() != 0) {
        std::cout << "Test Error: length0" << std::endl;
        return false;
    }
    if (v1->length() != (float)sqrt(3)) {
        std::cout << "Test Error: length1" << std::endl;
        return false;
    }
    if (v2->length() != (float)sqrt(12)) {
        std::cout << "Test Error: length2" << std::endl;
        return false;
    }

    if (v0->lengthSquared() != 0) {
        std::cout << "Test Error: lengthSquared0" << std::endl;
        return false;
    }
    if (v1->lengthSquared() != 3) {
        std::cout << "Test Error: lengthSquared1" << std::endl;
        return false;
    }
    if (v2->lengthSquared() != 12) {
        std::cout << "Test Error: lengthSquared2" << std::endl;
        return false;
    }
    Vector3* z = Vector3::ZERO();
    Vector3* v2Cv1 = Vector3::cross(*v2, *v1);
    if (!v2Cv1->nearlyEquals(*z)) {
        std::cout << "Test Error: cross0" << std::endl;
        return false;
    }
    Vector3* v1Cv2 = Vector3::cross(*v1, *v2);
    if (!v1Cv2->nearlyEquals(*z)) {
        std::cout << "Test Error: cross1" << std::endl;
        return false;
    }
    Vector3* v1Cv3 = Vector3::cross(*v1, *v3);
    Vector3* v1Cv3Test = new Vector3(-3, -2, 5);
    if (!v1Cv3->nearlyEquals(*v1Cv3Test)) {
        std::cout << "Test Error: cross2" << std::endl;
        return false;
    }
    Vector3* v2Cv3 = Vector3::cross(*v2, *v3);
    Vector3* v2Cv3Test = new Vector3(-6, -4, 10);
    if (!v2Cv3->nearlyEquals(*v2Cv3Test)) {
        std::cout << "Test Error: cross3" << std::endl;
        return false;
    }

    Vector3* v0Pv1 = Vector3::plus(*v0, *v1);
    if (!v0Pv1->nearlyEquals(*v1)) {
        std::cout << "Test Error: plus0" << std::endl;
        return false;
    }
    Vector3* v1Pv2 = Vector3::plus(*v1, *v2);
    Vector3* v1Pv2Test = new Vector3(3, 3, 3);
    if (!v1Pv2->nearlyEquals(*v1Pv2Test)) {
        std::cout << "Test Error: plus1" << std::endl;
        return false;
    }
    Vector3* v1Pv3 = Vector3::plus(*v1, *v3);
    Vector3* v1Pv3Test = new Vector3(-2, 3, 0);
    if (!v1Pv3->nearlyEquals(*v1Pv3Test)) {
        std::cout << "Test Error: plus 3" << std::endl;
        return false;
    }

    Vector3* v1Neg = Vector3::negate(*v1);
    if (!Vector3::minus(*v0, *v1)->nearlyEquals(*v1Neg)) {
        std::cout << "Test Error: minues0" << std::endl;
        return false;
    }
    if (!Vector3::minus(*v1, *v0)->nearlyEquals(*v1)) {
        std::cout << "Test Error: minus1" << std::endl;
        return false;
    }
    Vector3* v3Mv2Test = new Vector3(-5, 0, -3);
    if (!Vector3::minus(*v3, *v2)->nearlyEquals(*v3Mv2Test)) {
        std::cout << "Test Error: minus2" << std::endl;
        return false;
    }

    if (!Vector3::negate(*v0)->equals(*v0)) {
        std::cout << "Test Error: negate0" << std::endl;
        return false;
    }
    Vector3* v1Negate = new Vector3(-1, -1, -1);
    if (!Vector3::negate(*v1)->equals(*v1Negate)) {
        std::cout << "Test Error: negate1" << std::endl;
        return false;
    }
    Vector3* v1S2Test = new Vector3(2, 2, 2);
    if (!Vector3::scale(*v1, 2)->equals(*v1S2Test)) {
        std::cout << "Test Error: scale0" << std::endl;
        return false;
    }

    Vector3* n = new Vector3(0, 0, 1);
    Vector3* toLight = new Vector3(1 / sqrt(2), 0, 1 / sqrt(2));
    Vector3* reflection = Vector3::reflect(*toLight, *n);
    Vector3* testReflectVect = new Vector3(-1 / sqrt(2), 0, 1 / sqrt(2));
    if (!reflection->nearlyEquals(*testReflectVect)) {
        std::cout << "Test Error: reflect0" << std::endl;
        return false;
    }
    free(n); free(toLight); free(reflection); free(testReflectVect);
    n = new Vector3(1, 0, 0);
    toLight = new Vector3(0, 0, 1);
    reflection = Vector3::reflect(*toLight, *n);
    Vector3* testReflectVect2 = new Vector3(0, 0, -1);
    if (!reflection->nearlyEquals(*testReflectVect2)) {
        std::cout << "Test Error: reflect1" << std::endl;
        return false;
    }
    return true;
}
