/*
	Author: Jarrod Dowsey
	Description: Ground Surface for a world.
*/

#ifndef	GROUND_SURFACE_H
#define GROUND_SURFACE_H

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class FreeCamera;
class GroundSurface
{
public:

	GroundSurface(unsigned int programID, FreeCamera* camera);

	~GroundSurface();

	void GenerateGrid(unsigned int rows, unsigned int cols);

	void Draw();

	void GeneratePerlin(unsigned int rows, unsigned int cols);

	void GenerateGroundTextures(unsigned int& texture, const char* textureName);

private:

	FreeCamera* m_camera;

	glm::vec3 m_lightDirection;
	glm::mat4 m_lightMatrix;

	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_VBO;

	unsigned int m_indexCount;

	unsigned int m_programID;

	unsigned int m_texture;

	unsigned int m_perlin_texture;
	unsigned int m_grassTexture;
	unsigned int m_sandTexture;
	unsigned int m_waterTexture;


};

#endif