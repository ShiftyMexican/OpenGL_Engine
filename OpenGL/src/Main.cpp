#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Application.h"

#include <Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat4;


int main() 
{
	// For Solar System insert number 1 into constructor

	Application* theApp = new Application(2);
	theApp->Run();
	
	return 0;

}