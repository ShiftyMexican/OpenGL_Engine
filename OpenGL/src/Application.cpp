#include "Application.h"
#include "FreeCamera.h"
using glm::vec3;
using glm::vec4;
using glm::mat4;

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

Application::Application(int tutorialNumber)
{

	StartUp();

	//ShaderGeneration();

	m_tutorialNumber = tutorialNumber;

	// Initialization for the solar system which is tutorial 1 ------------------
	m_solar = new SolarSystem();
	m_planetRot = 0.0f;
	m_planetRot2 = 0.0f;
	//---------------------------------------------------------------------------

	// Initialization for the Free Camera ---------------------------------------
	myCamera = new FreeCamera(window);
	myCamera->SetupPerspective(glm::pi<float>() * 0.25f ,1240.0f / 768.0f);
	myCamera->LookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	//---------------------------------------------------------------------------

	// Robot Object-------------------------------------------------------------------------------------------------------
	myObject_Robot = new Object(window, m_programID, "./data/BattleDroid.obj", "./data/BattleDroid_Dif.bmp");
	// -------------------------------------------------------------------------------------------------------------------

	// Car Object --------------------------------------------------------------------------------------------------------
	myObject_Car = new Object(window, m_programID, "./data/PickUp.obj", "./data/pickup_exterior_d.png");
	//--------------------------------------------------------------------------------------------------------------------

	// For if i want to Generate a grid to the screen -------------------------
	/*
	m_rows = 10;
	m_cols = 10;
	generateGrid(m_rows, m_cols);
	*/
	// ------------------------------------------------------------------------
	

}

Application::~Application()
{
	Gizmos::destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
	return;
}

void Application::Run()
{	
	while(glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glEnable(GL_DEPTH_TEST);

		Update();
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Application::Update()
{

	m_currentTime = (float)glfwGetTime();
	deltaTime = m_currentTime - m_previousTime; 
	m_previousTime = m_currentTime;

	myCamera->Update(deltaTime);
	myObject_Robot->Update(deltaTime);
	myObject_Car->Update(deltaTime);

	Gizmos::clear();

	Gizmos::addSphere(myObject_Robot->GetLightPos(), 0.3f, 15, 15, vec4(1, 1, 0, 1));

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
}

void Application::Draw()
{
	glUseProgram(m_programID);

	unsigned int uiProjViewLocation = glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(uiProjViewLocation, 1, false, glm::value_ptr(myCamera->GetProjectionView()));


	uiProjViewLocation = glGetUniformLocation(m_programID, "diffuse");
	glUniform1i(uiProjViewLocation, 0);

	glBindVertexArray(m_VAO);

	myObject_Robot->Draw();
	myObject_Car->Draw();
	m_bar->Draw();

	Gizmos::addTransform(glm::mat4(1), 50.0f);

	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	//glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0); 

	Gizmos::draw(myCamera->GetProjectionView());
	glBindVertexArray(0);

}

// Function to create a grid
void Application::generateGrid( unsigned int rows, unsigned int cols ) 
{
	Vertex* aoVerticies = new Vertex[ rows * cols ];

	for( unsigned int r = 0; r < rows; r++ )
	{
		for( unsigned int c = 0; c < cols; c++ )
		{
			aoVerticies[ r * cols + c ].position = vec4((float)c - (cols / 2), 0, (float)r - (rows / 2), 1);

			vec3 colour = vec3( sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));

			//aoVerticies[ r * cols + c ].colour = vec4( 1, 1, 1, 1 );
		}
	}

	// IBO
	unsigned int* auiIndicies = new unsigned int[ (rows - 1) * (cols - 1) * 6 ];

	unsigned int index = 0;

	for( unsigned int r = 0; r < (rows - 1); r++)
	{
		for( unsigned int c = 0; c < (cols - 1); c++)
		{
			// Triangle 1
			auiIndicies[ index++ ] = r * cols + c;
			auiIndicies[ index++ ] = ( r + 1 ) * cols + c;
			auiIndicies[ index++ ] = ( r + 1 ) * cols + (c + 1);

			// Triangle 2
			auiIndicies[ index++ ] = r * cols + c;
			auiIndicies[ index++ ] = ( r + 1 ) * cols + (c + 1);
			auiIndicies[ index++ ] = r * cols + (c + 1);
		}
	}

	m_indexCount = index;

	//Create a new VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray( m_VAO );

	// Generate GL Buffers
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVerticies, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), auiIndicies, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));


	glBindVertexArray(0);


	delete[] aoVerticies;
	delete[] auiIndicies;
}

void Application::StartUp()
{
	if (glfwInit() == false)
	return;

	window = glfwCreateWindow(1240, 768, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr) 
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) 
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1);
	Gizmos::create();

	// Initalizing the AntTweak -----------------------------------------------
	m_bar = new MyAntTeakBar(window);
	// ------------------------------------------------------------------------

	HandleShader("./data/OBJ_Shader.vert", "./data/OBJ_Shader.frag");
}

unsigned int Application::LoadShader(const char* shaderName, unsigned int uiType)
{
	int success = GL_FALSE;

	unsigned int handle = glCreateShader(uiType);
	unsigned char* source = FileToBuffer(shaderName);

	glShaderSource(handle, 1, (const char**)&source, 0);
	glCompileShader(handle);

	//m_programID = glCreateProgram();
	//
	//glAttachShader(m_programID, handle);
	//glLinkProgram(m_programID);
	//
	//glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

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

unsigned char* Application::FileToBuffer(const char* a_strName)
{
	// open file for text reading
	FILE* pFile = fopen(a_strName, "rb");
	if (pFile == nullptr)
	{
		printf("Error: Unable to open file '%s' for reading!\n", a_strName);
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

	fclose(pFile);
	return acBuffer;
}

unsigned int Application::HandleShader(const char* a_vertexShader, const char* a_fragmentShader)
{
	// Loading my Shaders in --------------------------------------------------
	GLuint vertexShader		= LoadShader(a_vertexShader, GL_VERTEX_SHADER);
	GLuint fragmentShader	= LoadShader(a_fragmentShader, GL_FRAGMENT_SHADER);
	//-------------------------------------------------------------------------

	unsigned int uiShaderID = CreateProgram(vertexShader, fragmentShader);

	return uiShaderID;
}

unsigned int Application::CreateProgram(GLuint vs, GLuint fs)
{
	int success = GL_FALSE;

	m_programID = glCreateProgram();
	
	glAttachShader(m_programID, vs);
	glAttachShader(m_programID, fs);

	glLinkProgram(m_programID);
	
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetShaderInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);

		delete[] infoLog;
		return 0;
	}

	return m_programID;
}




