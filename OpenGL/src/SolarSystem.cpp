#include "SolarSystem.h"
#include "Camera.h"
#include "Application.h"


SolarSystem::SolarSystem()
{
	m_planetRot = 0.0f;
	m_planetRot2 = 0.0f;
	
}

SolarSystem::~SolarSystem()
{

}

void SolarSystem::Update(float deltaTime)
{
	m_deltaTime = deltaTime;

	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));
	vec4 white(1);
	vec4 black(1,1,1,1);
	
	for (int i = 0; i < 21; ++i) 
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}
	
	m_planetRot += 0.006f;
	m_planetRot2 += 0.0059f;
	
	Gizmos::addSphere(vec3(0), 1, 15, 15, vec4(1, 1, 0, 1));
	Gizmos::addSphere(vec3(2 * sin(m_planetRot), 0, 2 * cos(m_planetRot)), 0.2f, 20, 20, vec4(1, 0, 1, 1));
	Gizmos::addSphere(vec3(3.5 * sin(m_planetRot2), 0, 3.5 * cos(m_planetRot2)), 0.3f, 15, 15, vec4(0, 0, 1, 1));
	
}