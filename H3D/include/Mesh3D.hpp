#pragma once
#include <vector>
#include "Vertex3D.hpp"
#include "Textures.hpp"

class Mesh3D {
public:
	std::vector<Vertex3D> _vertices;
	std::shared_ptr<Texture> _texture;

	Mesh3D();
	~Mesh3D();

	void setTexture(std::shared_ptr<Texture> texture);
	void draw(bool highlight = false, float x = 0, float y = 0, float z = 0, float rx = 0, float ry = 0, float rz = 0);
};

std::shared_ptr<Mesh3D> generateCube(float size);