#pragma once

#include <iostream>
#include <vector>
#include "Scene.h"
#include "../core/Renderer.h"

class FPSGame : public Scene
{
public:
	FPSGame();
	~FPSGame();

	void SetMap(std::vector<glm::vec3> vertices);
	void SetController();
	void AddObject();
	void RemoveObject();
	void Update(float m);
	void Render();

	Renderer renderer;

private:
	Map* m_Map;
};