
#include "TokenizeOBJ.h"
#include <string>

using namespace RayTracerSpace;
/*
private:
		std::vector<std::string> _lineBuffer;
		std::string _filePath;
		std::ifstream _inputStream;
		std::string _line;
		std::vector<VertexInfo> vertices;
		std::vector<VertexInfo> vertexTextures;
		std::vector<VertexInfo> vertexNormals;
		std::vector<Faces> faces;
	public:
		TokenizeOBJ(std::string filePath);
		bool tokenizeOBJ();
*/
std::vector<std::string> splitString(const char c, std::string s, bool ignoreDoubles = true) {
	std::vector<std::string> splitLine = std::vector<std::string>();
	size_t pos = 0;
	while ((pos = s.find(c)) != std::string::npos) { // split on c
		if (ignoreDoubles && pos != 0) {
			splitLine.push_back(s.substr(0, pos));
		}
		s.erase(0, pos + 1); // 1 for length of c delimiter
	}
	if (s.length() != 0) splitLine.push_back(s); // add rest
	return splitLine;
}

TokenizeOBJ::TokenizeOBJ(std::string filePath) :
	_filePath(filePath),
	_lineBuffer(std::vector<std::string>()),
	_inputStream(std::ifstream(_filePath)),
	_line(""),
	_vertices(std::vector<VertexInfo>()),
	_vertexTextures(std::vector<VertexInfo>()),
	_vertexNormals(std::vector<VertexInfo>()),
	_faces(std::vector<Faces>()) {
}

std::vector<Faces> TokenizeOBJ::getFaces() {
	return _faces;
}

bool TokenizeOBJ::tokenizeOBJ() {
	if (!_inputStream) {
		std::cerr << "Can't open input file!";
		return false;
	}
	while (std::getline(_inputStream, _line)) {
		if ((_line.starts_with("v") && !_line.starts_with("vp")) || _line.starts_with("f")) {
			_lineBuffer.push_back(_line);
		}
	}
	_inputStream.close(); // done reading file
	std::cout << "Parsing OBJ file" << std::endl;
	std::cout << "  vertices: 0" << std::endl;
	std::cout << "  vertex normals: 0" << std::endl;
	std::cout << "  vertex textures: 0" << std::endl;
	std::cout << "  triangles: 0" << std::endl;
	for (int i = 0; i < _lineBuffer.size(); i++) {
		_line = _lineBuffer[i];
		size_t pos = 0;
		std::vector<std::string> splitLine = splitString(' ', _line);
		if (splitLine[0] == "v") { // vertex
			Vector3 ps = Vector3(std::stod(splitLine[1]), std::stod(splitLine[2]), std::stod(splitLine[3]));
			_vertices.push_back({ .type = OBJTYPE::vertex, .points = ps });
			std::cout << "\x1b[4A";
			std::cout << "  vertices: " << _vertices.size() << std::endl;
			std::cout << "  vertex normals: " << _vertexNormals.size() << std::endl;
			std::cout << "  vertex textures: " << _vertexTextures.size() << std::endl;
			std::cout << "  triangles: " << _faces.size() << std::endl;
		}
		else if (splitLine[0] == "vn") { // vertex normal
			Vector3 ps = Vector3(std::stod(splitLine[1]), std::stod(splitLine[2]), std::stod(splitLine[3]));
			_vertexNormals.push_back({ .type = OBJTYPE::vertexNormal, .points = ps });
			std::cout << "\x1b[3A";
			std::cout << "  vertex normals: " << _vertexNormals.size() << std::endl;
			std::cout << "  vertex textures: " << _vertexTextures.size() << std::endl;
			std::cout << "  triangles: " << _faces.size() << std::endl;
		}
		else if (splitLine[0] == "vt") { // vertex texture
			Vector3 ps = Vector3(std::stod(splitLine[1]), std::stod(splitLine[2]), std::stod(splitLine[3]));
			_vertexTextures.push_back({ .type = OBJTYPE::vertexTexture, .points = ps });
			std::cout << "\x1b[2A";
			std::cout << "  vertex textures: " << _vertexTextures.size() << std::endl;
			std::cout << "  triangles: " << _faces.size() << std::endl;
		}
		else if (splitLine[0] == "f") { // faces
			Faces face = {
				.vertices = std::vector<Vector3>(),
				.vertexTextures = std::vector<Vector3>(),
				.vertexNormals = std::vector<Vector3>(),
			};
			for (int i = 1; i < 4; i++) {
				std::vector<std::string> dividedLine = splitString('/', splitLine[i]);
				int vertexIndex = std::stoi(dividedLine[0]);
				int vertexTextureIndex = std::stoi(dividedLine[1]);
				int vertexNormalIndex = std::stoi(dividedLine[2]);
				Vector3 vertex = _vertices.at(vertexIndex - 1).points;
				Vector3 texture = _vertexTextures.at(vertexTextureIndex - 1).points;
				Vector3 normal = _vertexNormals.at(vertexNormalIndex - 1).points;
				face.vertices.push_back(vertex);
				face.vertexTextures.push_back(texture);
				face.vertexNormals.push_back(normal);
			}
			_faces.push_back(face);
			std::cout << "\x1b[1A";
			std::cout << "  triangles: " << _faces.size() << std::endl;
		}
		else {
			std::cerr << "invalid token: " << splitLine[0] << std::endl;
		}
	}
	/*
	std::cout << std::endl;
	for (const Faces f : _faces) {
		std::cout << std::endl;
		for (const Vector3 v : f.vertices) {
			std::cout << "v " << v.X << " " << v.Y << " " << v.Z << std::endl;
		}
		for (const Vector3 v : f.vertexTextures) {
			std::cout << "vt " << v.X << " " << v.Y << " " << v.Z << std::endl;
		}
		for (const Vector3 v : f.vertexNormals) {
			std::cout << "vn " << v.X << " " << v.Y << " " << v.Z << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "faces found: " << _faces.size() << std::endl;
	*/
	std::cout << "Parsing Complete" << std::endl;
	return true;
}
