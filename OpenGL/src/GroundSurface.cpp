#include "GroundSurface.h"
#include "Application.h"
#include <stb_image.h>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

// Default Constructor
GroundSurface::GroundSurface(unsigned int programID, FreeCamera* camera)
{
	m_programID = programID;
	m_camera = camera;
	m_indexCount = 0;

<<<<<<< HEAD
	GenerateGroundTextures(m_grassTexture, "Snow_Texture.jpg");
	GenerateGroundTextures(m_sandTexture, "Grass_Texture_2.jpg");
	GenerateGroundTextures(m_waterTexture, "Ice_Texture.jpg");
=======
	GenerateGroundTextures(m_grassTexture, "./data/Grass_texture.jpg");
	GenerateGroundTextures(m_sandTexture, "./data/Sand_Texture.jpg");
	GenerateGroundTextures(m_waterTexture, "./data/Water_Texture.jpg");
>>>>>>> parent of 98f534e... Adding .lib files, added the perlin seed being able to be changed using the GUI Bar
}

// Destruction
GroundSurface::~GroundSurface()
{

}

// Generates a grid to then draw to the screen
void GroundSurface::GenerateGrid(unsigned int rows, unsigned int cols)
{
	/*Vertex vertexData[] =
	{
		{ vec4(-100, 0,  100, 1), vec2(0, 1), vec3(0, 0, 0) },
		{ vec4( 100, 0,  100, 1), vec2(0, 1), vec3(0, 0, 0) },
		{ vec4( 100, 0, -100, 1), vec2(0, 1), vec3(0, 0, 0) },
		{ vec4(-100, 0, -100, 1), vec2(0, 1), vec3(0, 0, 0) },
	};

	unsigned int indexData[] =
	{
		0, 1, 2,
		0, 2, 3,
	};*/
	m_indexCount = (rows - 1) * (cols - 1) * 6;
	Vertex* aoVerticies = new Vertex[rows * cols];
	
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; c++)
		{
			aoVerticies[r * cols + c].position = vec4((float)c, 0, (float)r, 1);
	
			vec3 colour = vec3(sinf((c / (float)(cols - 1)) * (r / (float)(rows - 1))));
	
			//aoVerticies[ r * cols + c ]. = vec4(colour, 1 );
			aoVerticies[r * cols + c].texCoord = vec2((float)c / cols, (float)r / rows);
		}
	}
	
	// IBO
	unsigned int* auiIndicies = new unsigned int[m_indexCount];
	
	unsigned int index = 0;
	
	for (unsigned int r = 0; r < (rows - 1); ++r)
		{
			for (unsigned int c = 0; c < (cols - 1); ++c)
			{
				// Triangle 1
				auiIndicies[index++] = r * cols + c;
				auiIndicies[index++] = (r + 1) * cols + c;
				auiIndicies[index++] = (r + 1) * cols + (c + 1);
	
				// Triangle 2
				auiIndicies[index++] = r * cols + c;
				auiIndicies[index++] = (r + 1) * cols + (c + 1);
				auiIndicies[index++] = r * cols + (c + 1);
			}
		}
	

	//Create a new VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate GL Buffers
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVerticies, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), auiIndicies, GL_STATIC_DRAW);
	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)((sizeof(vec4))+(sizeof(vec2))));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	

	delete[] aoVerticies;
	delete[] auiIndicies;
	GeneratePerlin(rows, cols);

}

void GroundSurface::Draw()
{
	glUseProgram(m_programID);

	unsigned int uiProjViewLocation = glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(uiProjViewLocation, 1, false, glm::value_ptr(m_camera->GetProjectionView()));

	//unsigned int uiLightPositionLocation = glGetUniformLocation(m_programID, "LightPos");
	//glUniform3f(uiLightPositionLocation, 1.0f, 1.0f, 1.0f);
	//
	//unsigned int uiLightColourLocation = glGetUniformLocation(m_programID, "LightColour");
	//glUniform3f(uiLightColourLocation, 1.0f, 1.0f, 1.0f);
	//
	//unsigned int uiCameraLocation = glGetUniformLocation(m_programID, "CameraPos");
	//glUniform3fv(uiCameraLocation, 0, glm::value_ptr(m_camera->GetPosition())); // 0.0f, 1.0f, 0.0f); // glm::value_ptr(m_lightYPos));
	//
	//unsigned int uiSpecPow = glGetUniformLocation(m_programID, "SpecPow");
	//glUniform1f(uiSpecPow, 25.0f);
	
	/*
	int loc = glGetUniformLocation(m_programID, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &(m_camera->GetProjectionView()[0][0]));

	glm:mat4 textureSpaceOffset(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);

	glm::mat4 lightMatrix = textureSpaceOffset * m_lightMatrix;

	loc = glGetUniformLocation(m_programID, "LightMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &lightMatrix[0][0]);

	loc = glGetUniformLocation(m_programID, "lightDir");
	glUniform3fv(loc, 1, &m_lightDirection[0]);

	loc = glGetUniformLocation(m_programID, "shadowMap");
	glUniform1i(loc, 0);

	*/	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_perlin_texture);
	unsigned int loc = glGetUniformLocation(m_programID, "perlin_texture");
	glUniform1i(loc, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	unsigned int loc2 = glGetUniformLocation(m_programID, "grass_texture");
	glUniform1i(loc2, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_sandTexture);
	unsigned int loc3 = glGetUniformLocation(m_programID, "sand_texture");
	glUniform1i(loc3, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture);
	unsigned int loc4 = glGetUniformLocation(m_programID, "water_texture");
	glUniform1i(loc4, 3);


	glBindVertexArray(m_VAO);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

}

void GroundSurface::GeneratePerlin(unsigned int rows, unsigned int cols)
{

	int dims = rows;
	float *perlin_data = new float[rows * cols];
	float scale = (1.0f / dims) * 3;
	int octaves = 6;
	float perlin_seed = 0.9f;

	for (int x = 0; x < rows; ++x)
	{
		for (int y = 0; y < cols; ++y)
		{
			float amplitude = 1.0f;
			float persistence = 0.3f;

			perlin_data[y* dims + x] = 0;

			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, (float)o);
				//float perlin_sample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * 0.5f + 0.5f;
				float perlin_s = glm::perlin(vec3((float)x, (float)y, perlin_seed) *scale * freq) *0.5f + 0.5f;
				perlin_data[y * dims + x] += perlin_s * amplitude;
				amplitude *= persistence;
			}
		}
	}

	glGenTextures(1, &m_perlin_texture);
	glBindTexture(GL_TEXTURE_2D, m_perlin_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, rows, cols, 0, GL_RED, GL_FLOAT, perlin_data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void GroundSurface::GenerateGroundTextures(unsigned int& texture, const char* textureName)
{
	int imageWidth = 0, imageHeight = 0, imageFormat = 0;

	unsigned char* data = stbi_load(textureName, &imageWidth, &imageHeight, &imageFormat, STBI_default);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);
}