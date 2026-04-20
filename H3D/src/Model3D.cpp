#include "Model3D.hpp"

int Model3D::_nextID = 0;

Model3D::Model3D(float x, float y, float z, float rx, float ry, float rz) {

	_id = _nextID++;

	_x = x;
	_y = y;
	_z = z;

	_rx = rx;
	_ry = ry;
	_rz = rz;

	_meshes.clear();
	std::shared_ptr<Mesh3D> cubeMesh = generateCube(0.5f);
	cubeMesh->setTexture(getTexture(L"tex\\logo.png"));
	_meshes.push_back(cubeMesh);
}

Model3D::~Model3D() {

}

void Model3D::draw(int selectedModelId) {

	bool highlight = (selectedModelId == _id);
	
	for (auto& mesh : _meshes) {
		mesh->draw(highlight, _x, _y, _z, _rx, _ry, _rz);
	}
}