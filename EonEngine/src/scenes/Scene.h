#pragma once

#include <iostream>
#include <vector>
#include "map/map.h"
#include "../controller/controller.h" 
#include "objects/Objects.h"



class Scene
{
public:
	Scene();
	~Scene();

	void SetMap();
	void SetController();
	void AddObject();
	void RemoveObject();
	void Update();
	void Render();

private:
	Map* m_Map;
	Controller* m_Controller;
	std::vector<Object*> m_Objects;
};