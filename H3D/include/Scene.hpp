#pragma once
#include "Model3D.hpp"

class Scene {
public:
	std::vector<std::shared_ptr<Model3D>> _models;
	int _selectedModelId = -1;

	Scene();
	~Scene();
	
	void setViewport();
	void setProjection();
	void setCamera();

	void addModel(std::shared_ptr<Model3D> model);
	int getHoveredModelId();
	void drawModels();

	void update();
	void draw();
};

extern std::shared_ptr<Scene> scene;