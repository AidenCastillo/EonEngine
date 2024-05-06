#include "map.h"

void Map::init(std::string mapPath, std::string texture) {
	if (mapPath == "") {
		std::cout << "No map path provided" << std::endl;
		return;
	}
	if (texture == "") {
		std::cout << "No texture provided" << std::endl;
		return;
	}
}

void Map::SetVertices(std::vector<glm::vec3> vertices)
{
	this->vertices = vertices;
}

void Map::SetUVs(std::vector<glm::vec2> uvs)
{
	this->uvs = uvs;
}

void Map::SetNormals(std::vector<glm::vec3> normals)
{
	this->normals = normals;
}

void Map::SetTextureID(GLuint textureID)
{
	this->textureID = textureID;
}

void Map::SetMapCoordsVecSize(GLuint size)
{
	this->mapCoordsVecSize = size;
}

std::vector<glm::vec3> Map::GetVertices() {
	return vertices;
}

std::vector<glm::vec2> Map::GetUVs() {
	return uvs;
}

std::vector<glm::vec3> Map::GetNormals() {
	return normals;
}

GLuint Map::GetTextureID() {
	return textureID;
}

GLuint Map::GetMapCoordsVecSize() {
	return vertices.size();
}

