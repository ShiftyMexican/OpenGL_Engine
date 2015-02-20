#version 410

layout(location=0) in vec4 Position;
layout(location=1) in vec2 TexCoord;
layout(location=2) in vec3 Normal;

out vec3 vNormal;
out vec4 vPosition;
out vec2 vTexCoord;

uniform mat4 ProjectionView;

void main() 
{

	vNormal = Normal;
	vPosition = Position;
	vTexCoord = TexCoord; 
	gl_Position = ProjectionView * Position;
 
};