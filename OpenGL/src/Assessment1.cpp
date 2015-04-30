#include "Application.h"
#include "Assessment1.h"
#include "FreeCamera.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;

// Constructor
Assessment1::Assessment1(Application* app, GLFWwindow* window)
{
	m_application = app;
	m_window = window;

	// Calling of the Start up Function
	StartUp();
	//---------------------------------

	// Setting Perlin Seed
	m_perlinSeed = 835312.0f;

	// Initalizing the AntTweak ---------------------------------------------------
	m_bar = new MyAntTeakBar(window);
	m_bar->SetPerlinNoise(m_perlinSeed);
	//// ----------------------------------------------------------------------------

	// Initialization for the Free Camera ---------------------------------------
	myCamera = new FreeCamera(window);
	myCamera->SetupPerspective(glm::pi<float>() * 0.25f, 1240.0f / 768.0f);
	myCamera->LookAt(vec3(50, 50, 50), vec3(0), vec3(0, 1, 0));
	myCamera->SetFlySpeed(1000.0f);
	//---------------------------------------------------------------------------

	// Masterchief FBX----------------------------------------------------------------------------------------------------
	m_masterchief = new FBXObject(window, m_fbxProgram, myCamera, "pyro.fbx");
	//--------------------------------------------------------------------------------------------------------------------

	// Creating Emitter --------------------------------------------------------------------------------------------------
	m_emitter = new ParticleEmitter(myCamera);
	m_emitter->initialize(1000, 1.0f, 5.0f, 5, 20, 0.3f, 0.1f, glm::vec4(1, 1, 1, 1), glm::vec4(0.5, 0.5, 0.5, 0.5f));
	// ------------------------------------------------------------------------------------------------------------------

	// Render Target ----------------------------------------------------------
	//m_renderTarget = new RenderTarget(m_renderTargetProgram);
	//m_renderTarget->Init();
	//-------------------------------------------------------------------------

	// The Ground Surface------------------------------------------------------
	m_ground = new GroundSurface(m_surfaceProgram, myCamera);
	m_ground->SetPerlinSeed(m_perlinSeed);
	m_ground->GenerateGrid(200, 200);
	//-------------------------------------------------------------------------

	// The Ground Surface------------------------------------------------------
	m_skybox = new Skybox(m_skyboxProgram, myCamera);
	//-------------------------------------------------------------------------

	// Shadows-----------------------------------------------------------------
	//m_shadow = new Shadow(m_shadowProgram, m_shadowGenProgram, myCamera);
	//m_shadow->Init();
	//-------------------------------------------------------------------------

	Gizmos::create();

	// Robot Object-------------------------------------------------------------------------------------------------------
	myObject_Robot = new Object(window, myCamera, m_programID, "BattleDroid.obj", "BattleDroid_Dif.bmp");
	// -------------------------------------------------------------------------------------------------------------------

	// Car Object --------------------------------------------------------------------------------------------------------
	//myObject_Car = new Object(window, myCamera, m_programID, "PickUp.obj", "pickup_exterior_d.png");
	//--------------------------------------------------------------------------------------------------------------------

	m_previousTime = 0.0f;

	m_lightDir = vec3(1, 0, 1);
	m_lightColour = vec3(1, 1, 1);

	m_bar->SetLightDirX(1);
	m_bar->SetLightDirZ(1);

}

// Destructor
Assessment1::~Assessment1()
{
	Gizmos::destroy();

	//	delete myObject_Robot;
	//	delete myObject_Car;
	delete m_masterchief;
	delete m_renderTarget;

	glfwDestroyWindow(m_window);
	glfwTerminate();
	return;
}

// Run Program - Main Function to call the Application to Run
void Assessment1::Run()
{
	//// Main Game loop
	//while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	//{
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glEnable(GL_DEPTH_TEST);

	//	// Call Update
	//	Update();
	//	Draw();

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
}

// Start Up Function - Contains Data needed to start Various things without the project
// eg: Handling Shaders and Setting Window size
void Assessment1::StartUp()
{
	// Creating my Shader Programs----------------------------------------------------------------------
	m_programID = m_application->HandleShader("OBJ_Shader.vert", "OBJ_Shader.frag", 0);
	m_fbxProgram = m_application->HandleShader("FBX_Shader.vert", "FBX_Shader.frag", 0);
	m_renderTargetProgram = m_application->HandleShader("RenderTarget.vert", "RenderTarget.frag", 0);
	m_surfaceProgram = m_application->HandleShader("Perlin_Shader.vert", "Perlin_Shader.frag", 0);
	m_skyboxProgram = m_application->HandleShader("Skybox_Shader.vert", "Skybox_Shader.frag", 0);
	//--------------------------------------------------------------------------------------------------
}

// Update Function
void Assessment1::Update(float deltaTime)
{
	// Camera Update-----------------------------------------------------------
	myCamera->Update(deltaTime);
	//-------------------------------------------------------------------------

	// Update for FBX Oject - Masterchief--------------------------------------
	m_masterchief->Update(deltaTime);
	//-------------------------------------------------------------------------

	//myObject_Robot->Update(deltaTime);
	//myObject_Car->Update(deltaTime);

	if (m_ground->GetPerlinNoise() != m_bar->GetPerlinSeed())
	{
		m_ground->SetPerlinSeed(m_bar->GetPerlinSeed());
		m_ground->GenerateGrid(200, 200);
	}

	if (m_lightDir.x != m_bar->GetLightDirX())
	{
		m_lightDir.x = m_bar->GetLightDirX();
	}

	if (m_lightDir.z != m_bar->GetLightDirZ())
	{
		m_lightDir.z = m_bar->GetLightDirZ();
	}

	if (m_lightColour != m_bar->GetLightColour())
	{
		m_lightColour = m_bar->GetLightColour();
	}

	if (m_ground->GetIceLevel() != m_bar->GetIceLevel())
	{
		m_ground->SetIceLevel(m_bar->GetIceLevel());
	}

	if (m_ground->GetAmp() != m_bar->GetAmp())
	{
		m_ground->SetAmp(m_bar->GetAmp());
		m_ground->GenerateGrid(200, 200);
	}

	//-------------------------------------------------------------------------
	if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS) {
		m_programID = m_application->HandleShader("OBJ_Shader.vert", "OBJ_Shader.frag", 0);
		m_fbxProgram = m_application->HandleShader("FBX_Shader.vert", "FBX_Shader.frag", 0);
		m_renderTargetProgram = m_application->HandleShader("RenderTarget.vert", "RenderTarget.frag", 0);
		m_surfaceProgram = m_application->HandleShader("Perlin_Shader.vert", "Perlin_Shader.frag", 0);
		m_skyboxProgram = m_application->HandleShader("Skybox_Shader.vert", "Skybox_Shader.frag", 0);
	}
}


// Draw Function
void Assessment1::Draw()
{
	Gizmos::clear();
	// Sets the Render Target for all Draws Following-------------------
	//m_renderTarget->SetAsActiveRenderTarget();
	//------------------------------------------------------------------

	//Gizmos::addSphere(m_masterchief->GetLightPos(), 2, 10, 10, vec4(1, 0, 0, 1));

	m_skybox->Draw();


	// Drawing the Ground Surface--------
	m_ground->Draw(m_lightDir, m_lightColour);
	//-----------------------------------

	myObject_Robot->Draw(m_lightDir, m_lightColour);
	//myObject_Car->Draw(m_lightDir, m_lightColour);

	// Drawing the Character-------------
	m_masterchief->Draw(m_lightDir, m_lightColour);
	//-----------------------------------

	//m_shadow->Draw();

	// Drawing of the Particles----------------------------------------------------------------------
	m_emitter->Draw((float)glfwGetTime(), myCamera->GetTransform(), myCamera->GetProjectionView());
	//-----------------------------------------------------------------------------------------------

	Gizmos::draw(myCamera->GetProjectionView());

	// Clearing the Render Target ---------------------------------------------
	//m_renderTarget->ClearActiveRenderTarget();
	//-------------------------------------------------------------------------

	// Drawing Everything that is currently on the render target
	//m_renderTarget->Draw();

	// GUI Draw-------------------------
	m_bar->Draw();
	//----------------------------------


	//Gizmos::addTransform(glm::mat4(1), 50.0f);
	//
	//Gizmos::draw(myCamera->GetProjectionView());
}


