#include "ObjLoader.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

bool ObjLoader::LoadObj(const char* filename, std::vector<Vector4>& vertices, std::vector<Vector2>& uvs, std::vector<Vector3>& normals, std::vector<unsigned int>& indices) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Cannot open file %s", filename);
		return false;
	}

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Vector4> tempVertices;
	std::vector<Vector3> tempNormals;
	std::vector<Vector2> tempUVs;

	char lineHeader[128], emptyLine[1024];
	while (fscanf(file, "%s", lineHeader) != EOF) {
		if (strcmp(lineHeader, "v") == 0) {
			Vector4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

			tempVertices.push_back(vertex);
		} else if (strcmp(lineHeader, "vt") == 0) {
			Vector2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);

			tempUVs.push_back(uv);
		} else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

			tempNormals.push_back(normal);
		} else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int read = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", 
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if (read != 9) {
				fprintf(stderr, "Could not parse file\n");
				return false;
			}

			for (int i = 2; i >= 0; --i) {
				vertexIndices.push_back(vertexIndex[i]);
				uvIndices.push_back(uvIndex[i]);
				normalIndices.push_back(normalIndex[i]);
			}
		} else {
			fgets(emptyLine, 1024, file);
		}
	}

	std::map<PackedVertex, unsigned int> myMap;
	for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
		Vector4 vertex = tempVertices[vertexIndices[i] - 1];
		Vector2 uv = tempUVs[uvIndices[i] - 1];
		Vector3 normal = tempNormals[normalIndices[i] - 1];
		PackedVertex packedVertex(vertex, uv, normal);

		std::map<PackedVertex, unsigned int>::iterator it = myMap.find(packedVertex);
		if (it != myMap.end()) {
			indices.push_back(it->second);
		} else {
			vertices.push_back(vertex);
			uvs.push_back(uv);
			normals.push_back(normal);

			unsigned int newIndex = (unsigned int)vertices.size() - 1;
			indices.push_back(newIndex);
			myMap[packedVertex] = newIndex;
		}
	}

	return true;
}