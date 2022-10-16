
#ifndef TOKENIZEOBJ_H
#define TOKENIZEOBJ_H

#include "includes/Vector3.h"

#include <fstream>
#include <iostream>
#include <vector>

namespace RayTracerSpace {
	/*
	vertex,				// geometric vetices		(x, y, z [, w])		0-1.0
	vertexTexture,		// texture coordinates		(u [, v, w])		0-1.0
	vertexNormal,		// vertex normals			(x, y, z)
	vertexParameter,	// parameter space vertices	(u [, v] [, w])
	faces,				// polygonal face elements
	*/
	enum struct OBJTYPE {
		vertex,				// (x, y, z [, w])	// ignoring w
		vertexTexture,		// (u [, v, w])		// presuming v and w
		vertexNormal,		// (x, y, z)
		vertexParameter		// (u [, v] [, w])	// presuming v and w
	};
	struct VertexInfo {	
		OBJTYPE type;
		Vector3 points;
	};
	struct Faces {
		std::vector<Vector3> vertices;
		std::vector<Vector3> vertexTextures;
		std::vector<Vector3> vertexNormals;
	};
	class TokenizeOBJ {
	private:
		std::vector<std::string> _lineBuffer;
		std::string _filePath;
		std::ifstream _inputStream;
		std::string _line;
		std::vector<VertexInfo> _vertices;
		std::vector<VertexInfo> _vertexTextures;
		std::vector<VertexInfo> _vertexNormals;
		std::vector<Faces> _faces;
	public:
		TokenizeOBJ(std::string filePath);
		bool tokenizeOBJ();
		std::vector<Faces> getFaces();
	};
}

#endif
