/*	
	Author: Jarrod Dowsey
	Description: Simple Applicatuion class
*/

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SolarSystem.h"
#include "Object.h"
#include "MyAntTweakBar.h"

#ifndef APPLICATION_H
#define APPLICATION_H

struct Vertex;

class FreeCamera;
class Application
{
public:

	// Constructor
	Application(int tutorialNumber);

	// Destructor
	~Application();

	void Run();

	void Update();

	void Draw();

	void StartUp();

	float deltaTime;

	GLFWwindow* window;

	unsigned int HandleShader(const char* vertexShader, const char* fragmentShader);

	unsigned int LoadShader(const char* shaderName, unsigned int uiType);

	unsigned char* FileToBuffer(const char* a_strName);

	unsigned int CreateProgram(GLuint vs, GLuint fs);

protected:

	
	SolarSystem* m_solar;
	FreeCamera* myCamera;
	Object* myObject_Robot;
	Object* myObject_Car;
	MyAntTeakBar* m_bar;

	glm::mat4 view;
	glm::mat4 projection;

	float m_planetRot;
	float m_planetRot2;

	int m_tutorialNumber;

	float m_currentTime;
	float m_previousTime;
	
	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_VBO;

	unsigned int m_indexCount;

	void generateGrid( unsigned int rows, unsigned int cols );

	unsigned int m_programID;

	unsigned int m_rows;
	unsigned int m_cols;
};

#endif