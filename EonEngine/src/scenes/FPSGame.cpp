#include "FPSGame.h"

#include <iostream>
#include "../core/VertexArray.h"
#include "../core/VertexBuffer.h"
#include "../core/demoShader.h"
#include "../core/Texture.h"
#include "../core/IndexBuffer.h"
#include "../core/VertexBufferLayout.h"
#include "../core/Renderer.h"



FPSGame::FPSGame()
	: m_Map(nullptr)
{
	Renderer renderer;
	

}
FPSGame::~FPSGame()
{
}

void FPSGame::SetMap(std::vector<glm::vec3> vertices)
{
}

void FPSGame::SetController()
{
}

void FPSGame::AddObject()
{
}

void FPSGame::RemoveObject()
{
}

void FPSGame::Update(float m)
{
}

void FPSGame::Render()
{
	
}

