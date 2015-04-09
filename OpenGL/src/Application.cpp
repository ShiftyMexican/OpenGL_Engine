#include "Application.h"
#include "FreeCamera.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;

// Constructor
Application::Application(int tutorialNumber)
{
	// Calling of the Start up Function
	StartUp();
	m_tutorialNumber = tutorialNumber;
	//---------------------------------

	// Setting Perlin Seed
	m_perlinSeed = 835312.0f;

	// Initalizing the AntTweak ---------------------------------------------------
	m_bar = new MyAntTeakBar(window);
	m_bar->SetPerlinNoise(m_perlinSeed);
	//// ----------------------------------------------------------------------------
	//
	//// Initialization for the solar system which is tutorial 1 ------------------
	//m_solar = new SolarSystem();
	//m_planetRot = 0.0f;
	//m_planetRot2 = 0.0f;

	// Initialization for the solar system which is tutorial 1 ------------------
	//m_solar = new SolarSystem();
	//m_planetRot = 0.0f;
	//m_planetRot2 = 0.0f;
	//---------------------------------------------------------------------------

	// Initialization for the Free Camera ---------------------------------------
	myCamera = new FreeCamera(window);
	myCamera->SetupPerspective(glm::pi<float>() * 0.25f ,1240.0f / 768.0f);
	myCamera->LookAt(vec3(50, 50, 50), vec3(0), vec3(0, 1, 0));
	myCamera->SetFlySpeed(50.0f);
	//---------------------------------------------------------------------------

	// Masterchief FBX----------------------------------------------------------------------------------------------------
	//m_masterchief = new FBXObject(window, m_programID, myCamera, "./data/Bunny.fbx");
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
	myObject_Car = new Object(window, myCamera, m_programID, "PickUp.obj", "pickup_exterior_d.png");
	//--------------------------------------------------------------------------------------------------------------------
	
	m_previousTime = 0.0f;

	m_lightDir = vec3(1, 0, 1);
	m_lightColour = vec3(1, 1, 1);

	m_bar->SetLightDirX(1);
	m_bar->SetLightDirZ(1);
}

// Destructor
Application::~Application()
{
	Gizmos::destroy();

//	delete myObject_Robot;
//	delete myObject_Car;
	delete m_masterchief;
	delete m_renderTarget;

	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}

// Run Program - Main Function to call the Application to Run
void Application::Run()
{	
	// Main Game loop
	while(glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);

		// Call Update
		Update();
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

// Start Up Function - Contains Data needed to start Various things without the project
// eg: Handling Shaders and Setting Window size
void Application::StartUp()
{
	if (glfwInit() == false)
		return;

	// Initializing the Screen size to 1240x768------------------------------------
	window = glfwCreateWindow(1240, 768, "Computer Graphics", nullptr, nullptr);
	//-----------------------------------------------------------------------------

	// Deleteing the window if null------------------------------------------------
	if (window == nullptr)
	{
		glfwTerminate();
		return;
	}
	//-----------------------------------------------------------------------------

	// Making the Window context current-------------------------------------------
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}
	//----------------------------------------------------------------------------

	// Setting the Colour of the window--------------------------------------------
	glClearColor(0.1f, 0.1f, 0.1f, 1);
	//glEnable(GL_FRONT_AND_BACK);
	//-----------------------------------------------------------------------------
	
	// Creating my Shader Programs----------------------------------------------------------------------
	m_programID = HandleShader("OBJ_Shader.vert", "OBJ_Shader.frag", 0);
	m_renderTargetProgram = HandleShader("RenderTarget.vert", "RenderTarget.frag", 0);
	m_surfaceProgram = HandleShader("Perlin_Shader.vert", "Perlin_Shader.frag", 0);
	//m_shadowProgram = HandleShader("Shadow_Shader.vert", "Shadow_Shader.frag", 0);
	//m_shadowGenProgram = HandleShader("Shadow_Gen.vert", "Shadow_Gen.frag", 0);
	m_skyboxProgram = HandleShader("Skybox_Shader.vert", "Skybox_Shader.frag", 0);
	//--------------------------------------------------------------------------------------------------
}

// Update Function
void Application::Update()
{
	// Creating DeltaTime Calculations-----------------------------------------
	m_currentTime = (float)glfwGetTime();
	deltaTime = m_currentTime - m_previousTime; 
	m_previousTime = m_currentTime;
	//-------------------------------------------------------------------------

	// Camera Update-----------------------------------------------------------
	myCamera->Update(deltaTime);
	//-------------------------------------------------------------------------

	// Update for FBX Oject - Masterchief--------------------------------------
	//m_masterchief->Update(deltaTime);
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


	// Switch Statement for if i am loading multiple tutorials-----------------
	 
	switch (m_tutorialNumber)
	{

	case 1:
		{
			m_solar->Update(deltaTime);
		}
		break;

	default:
		
		break;
	}
	
	//-------------------------------------------------------------------------
}

// Draw Function
void Application::Draw()
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
	myObject_Car->Draw(m_lightDir, m_lightColour);

	// Drawing the Character-------------
	//m_masterchief->Draw();
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

// Load Shader Function
unsigned int Application::LoadShader(const char* shaderName, unsigned int uiType)
{
	int success = GL_FALSE;

	unsigned int handle = glCreateShader(uiType);
	unsigned char* source = FileToBuffer(shaderName);

	glShaderSource(handle, 1, (const char**)&source, 0);
	glCompileShader(handle);

	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(handle, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
		return 0;
	}

	delete[] source;

	return handle;
}

// Reads the Shaders in from File
unsigned char* Application::FileToBuffer(const char* a_strName)
{
	// open file for text reading
	FILE* pFile = fopen(a_strName, "rb");
	if (pFile == nullptr)
	{
		printf_s("Error: Unable to open file '%s' for reading!\n", a_strName);
		return nullptr;
	}

	// get number of bytes in file
	fseek(pFile, 0, SEEK_END);
	unsigned int uiLength = (unsigned int)ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	// allocate buffer and read file contents
	unsigned char* acBuffer = new unsigned char[uiLength + 1];
	memset(acBuffer, 0, uiLength + 1);
	fread(acBuffer, sizeof(unsigned char), uiLength, pFile);

	acBuffer[uiLength] = '\0';

	fclose(pFile);
	return acBuffer;
}

// Hanldes the Shaders
unsigned int Application::HandleShader(const char* a_vertexShader, const char* a_fragmentShader, const char* a_geometryShader)
{
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint geometryShader = 0;
	GLuint updateShader = 0;
	// Loading my Shaders in --------------------------------------------------
	vertexShader = LoadShader(a_vertexShader, GL_VERTEX_SHADER);
	fragmentShader = LoadShader(a_fragmentShader, GL_FRAGMENT_SHADER);
	//-------------------------------------------------------------------------

	if (a_geometryShader != nullptr)
	{
		geometryShader = LoadShader(a_geometryShader, GL_GEOMETRY_SHADER);
	}

	unsigned int uiShaderID = CreateProgram(vertexShader, fragmentShader, geometryShader);

	return uiShaderID;
}

// Creates the programs and attatches shaders to them
unsigned int Application::CreateProgram(GLuint vs)
{
	int success = GL_FALSE;

	unsigned int programID = glCreateProgram();

	glAttachShader(programID, vs);

	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
		return 0;
	}

	glDeleteShader(vs);

	return programID;
}

// Creates the programs and attatches shaders to them 
unsigned int Application::CreateProgram(GLuint vs, GLuint fs, GLuint gs)
{
	int success = GL_FALSE;

	unsigned int programID = glCreateProgram();
	
	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glAttachShader(programID, gs);

	glLinkProgram(programID);
	
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
		return 0;
	}

	return programID;
}


