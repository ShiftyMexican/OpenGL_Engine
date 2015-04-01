/*
	Author: Jarrod Dowsey
	Descrition: OpenGL Solar System
*/

#ifndef	SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera;
class Application;
class SolarSystem
{
public:

	SolarSystem();

	~SolarSystem();

	void Update(float deltaTime);


private:

	Application* myApp;

	float m_planetRot;
	float m_planetRot2;

	float m_deltaTime;
};

#endif