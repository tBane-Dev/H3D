#pragma once
#include <vector>
#include "Vertex3D.hpp"
#include "Mesh3D.hpp"
#include "Textures.hpp"

class Model3D {
public:
	static int _nextID;
	int _id;
	float _x, _y, _z;
	float _rx, _ry, _rz; 
	std::vector<std::shared_ptr<Mesh3D>> _meshes;

	Model3D(float x = 0, float y = 0, float z = 0, float rx = 0, float ry = 0, float rz = 0);
	~Model3D();

	void draw(int selectedModelId);
};