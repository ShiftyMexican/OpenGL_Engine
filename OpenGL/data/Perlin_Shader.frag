#version 410

in vec2 frag_texcoord;

out vec4 out_color;
uniform sampler2D perlin_texture;
uniform sampler2D grass_texture;
uniform sampler2D sand_texture;
uniform sampler2D water_texture;

void main()
{

	float height = texture(perlin_texture, frag_texcoord).r; 
	float blendAmount = 0.6;

	vec4 grass, sand, water;

<<<<<<< HEAD
	grass = texture2D(grass_texture, vec2(frag_texcoord.x * 4, frag_texcoord.y * 4)); // This is now snow
	sand = texture2D(sand_texture, vec2(frag_texcoord.x * 10, frag_texcoord.y * 10)); // This is the Grass now
	water = texture2D(water_texture, vec2(frag_texcoord.x * 5, frag_texcoord.y * 5)); // Ice now
=======
	grass = texture2D(grass_texture, vec2(frag_texcoord.x * 15, frag_texcoord.y * 15));
	sand = texture2D(sand_texture, vec2(frag_texcoord.x * 10, frag_texcoord.y * 10));
	water = texture2D(water_texture, vec2(frag_texcoord.x * 100, frag_texcoord.y * 100));
>>>>>>> parent of 98f534e... Adding .lib files, added the perlin seed being able to be changed using the GUI Bar

	//out_color = texture(perlin_texture, frag_texcoord).rrrr;
	if(height > 0.7) 
	{
		out_color = grass;
	}
	else if(height > 0.58 && height < 0.7)
	{
<<<<<<< HEAD
		//out_color = (1 - blendAmount) * grass + blendAmount * sand;
		out_color = mix(grass, sand, 0.25);
=======
		out_color = (1 - blendAmount) * grass + blendAmount * sand;
>>>>>>> parent of 98f534e... Adding .lib files, added the perlin seed being able to be changed using the GUI Bar
	}
	else if(height > 0.55 && height < 0.65)
	{
		out_color = sand;
	}
	else if(height < 0.55)
	{
		out_color = water;
	}

	out_color.a = 1;
}