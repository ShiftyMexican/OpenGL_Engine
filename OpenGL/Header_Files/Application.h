/*	
	Author: Jarrod Dowsey
	Description: Simple Applicatuion class
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gizmos.h>
#include <fstream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SolarSystem.h"
#include "MyAntTweakBar.h"
#include "FBXObject.h"
#include "ParticleSystem.h"
#include "RenderTarget.h"
#include "GroundSurface.h"
#include "Shadow.h"
#include "SkyBox.h"

struct GridVertex {

	glm::vec4 position;
	glm::vec4 colour;
};

struct Vertex {

	glm::vec4 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

class Object;
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

	unsigned int HandleShader(const char* vertexShader, const char* fragmentShader, const char* a_geometryShader);

	unsigned int LoadShader(const char* shaderName, unsigned int uiType);

	unsigned char* FileToBuffer(const char* a_strName);

	unsigned int CreateProgram(GLuint vs, GLuint fs, GLuint gs);

	unsigned int CreateProgram(GLuint vs);


protected:
	// Window
	GLFWwindow* window;

	// Solar System Object
	SolarSystem* m_solar;

	// Camera Object
	FreeCamera* myCamera;

	// OBJ object - Robot
	Object* myObject_Robot;

	// OBJ object - Car
	Object* myObject_Car;

	// GUI Bar
	MyAntTeakBar* m_bar;

	// FBX object - Alien Guy
	FBXObject* m_masterchief;

	// Surface Object
	GroundSurface* m_ground;

	// Shadows
	Shadow* m_shadow;

	// SkyBox
	Skybox* m_skybox;

	glm::mat4 view;
	glm::mat4 projection;

	float m_planetRot;
	float m_planetRot2;

	int m_tutorialNumber;

	float m_currentTime;
	float m_previousTime;
	
	// Program for the Surface-----------
	unsigned int m_surfaceProgram;
	// ----------------------------------

	unsigned int m_shadowProgram;
	unsigned int m_shadowGenProgram;

	unsigned int m_skyboxProgram;

	// Particle Emitter------------------
	ParticleEmitter* m_emitter;

	unsigned int m_updateShader;
	unsigned int m_programID;
	unsigned int m_praticleProgramID;
	unsigned int m_particleUpdate;
	// ----------------------------------

	// Rendering Object------------------
	RenderTarget* m_renderTarget;

	unsigned int m_renderTargetProgram;
	//-----------------------------------
};

#endif