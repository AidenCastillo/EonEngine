#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

class Map
{
public:
	Map();
	~Map();
	void init(std::string path, std::string texture);
	void SetVertices(std::vector<glm::vec3> vertices);
	void SetUVs(std::vector<glm::vec2> uvs);
	void SetNormals(std::vector<glm::vec3> normals);
	void SetTextureID(GLuint textureID);
	void SetMapCoordsVecSize(GLuint size);

	std::vector<glm::vec3> GetVertices();
	std::vector<glm::vec2> GetUVs();
	std::vector<glm::vec3> GetNormals();
	std::vector<GLuint> GetIndices();
	GLuint GetTextureID();
	GLuint GetMapCoordsVecSize();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	GLuint textureID = -1;
	GLuint mapCoordsVecSize = 0;
};