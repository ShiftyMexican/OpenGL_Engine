#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec2 texcoord;
layout(location=2) in vec3 normal;

uniform mat4 ProjectionView;

out vec2 frag_texcoord;

uniform sampler2D perlin_texture;

void main()
{
	vec4 pos = position;

	float height = texture(perlin_texture, texcoord).r;
	if(height <= 0.52) 
	{
		height = 0.52;
	}

	pos.y += height * 30;
	frag_texcoord = texcoord;
	gl_Position = ProjectionView * pos;
}