#include "MyAntTweakBar.h"

MyAntTeakBar::MyAntTeakBar(GLFWwindow* window)
{
	m_clearColour = glm::vec4(0);
	m_perlinNoiseSeed = 0;
	TwInit(TW_OPENGL_CORE, nullptr);
	TwWindowSize(1240, 768);

	m_bar = TwNewBar("my bar");

	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetCursorPosCallback(window, OnMousePosition);
	glfwSetScrollCallback(window, OnMouseScroll);
	glfwSetKeyCallback(window, OnKey);
	glfwSetCharCallback(window, OnChar);
	glfwSetWindowSizeCallback(window, OnWindowResize);

	//TwAddVarRW(m_bar, "clear colour", TW_TYPE_COLOR4F, &m_clearColour[0], "");
	TwAddVarRW(m_bar, "Light direction", TW_TYPE_DIR3F, &m_light[0], "group=Light");
	TwAddVarRW(m_bar, "Light colour", TW_TYPE_DIR3F, &m_lightColour[0], "group=Light");
	TwAddVarRW(m_bar, "Perlin Noise Seed", TW_TYPE_FLOAT, &m_perlinNoiseSeed, "group=Ground");
}

MyAntTeakBar::~MyAntTeakBar()
{
	TwDeleteAllBars();
	TwTerminate();
}

void MyAntTeakBar::Update(float deltaTime)
{
	
}

void MyAntTeakBar::Draw()
{
	glClearColor(m_clearColour.r, m_clearColour.g, m_clearColour.b, m_clearColour.a);
	TwDraw();
}

glm::vec4 MyAntTeakBar::GetClearColour()
{
	return m_clearColour;
}

float MyAntTeakBar::GetPerlinSeed()
{
	return m_perlinNoiseSeed;
}

void MyAntTeakBar::SetPerlinNoise(float value)
{
	m_perlinNoiseSeed = value;
}

