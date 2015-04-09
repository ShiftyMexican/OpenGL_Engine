#version 410

in vec2 frag_texcoord;
in vec3 vNormal;
in vec4 vPosition;

out vec4 out_color;

uniform sampler2D perlin_texture;
uniform sampler2D grass_texture;
uniform sampler2D sand_texture;
uniform sampler2D water_texture;

uniform sampler2D diffuse;
uniform sampler2D normal;	

uniform vec3 LightDir;
uniform vec3 LightPos;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform float SpecPow;

void main()
{

	// Lighting
	vec3 N = texture(normal, frag_texcoord).xyz * 2 - 1;

	float d = max(0.0, dot(normalize(vNormal), normalize(LightDir) ) );	

	vec3 E = normalize( CameraPos - vPosition.xyz );
	
	vec3 R = reflect( -LightDir, vNormal.xyz );

	float s = max( 0, dot( E, R ) );
	
	s = pow( s, SpecPow );

	float height = texture(perlin_texture, frag_texcoord).r; 
	float blendAmount = 0.6;

	vec4 grass, sand, water;

<<<<<<< HEAD
<<<<<<< HEAD
	grass = texture2D(grass_texture, vec2(frag_texcoord.x * 4, frag_texcoord.y * 4)); // This is now snow
	sand = texture2D(sand_texture, vec2(frag_texcoord.x * 10, frag_texcoord.y * 10)); // This is the Grass now
	water = texture2D(water_texture, vec2(frag_texcoord.x * 5, frag_texcoord.y * 5)); // Ice now
=======
	grass = texture2D(grass_texture, vec2(frag_texcoord.x * 15, frag_texcoord.y * 15));
	sand = texture2D(sand_texture, vec2(frag_texcoord.x * 10, frag_texcoord.y * 10));
	water = texture2D(water_texture, vec2(frag_texcoord.x * 100, frag_texcoord.y * 100));
>>>>>>> parent of 98f534e... Adding .lib files, added the perlin seed being able to be changed using the GUI Bar
=======
	grass = texture2D(grass_texture, vec2(frag_texcoord.x * 4, frag_texcoord.y * 4)); // This is now snow
	sand = texture2D(sand_texture, vec2(frag_texcoord.x * 10, frag_texcoord.y * 10)); // This is the Grass now
	water = texture2D(water_texture, vec2(frag_texcoord.x * 5, frag_texcoord.y * 5)); // Ice now
>>>>>>> 9f15d9686915c53f8f70fe1cd0835ab9953780b5

	//out_color = texture(perlin_texture, frag_texcoord).rrrr;
	if(height > 0.7) 
	{
		out_color = grass;
	}
	else if(height > 0.58 && height < 0.7)
	{
<<<<<<< HEAD
<<<<<<< HEAD
		//out_color = (1 - blendAmount) * grass + blendAmount * sand;
		out_color = mix(grass, sand, 0.25);
=======
		out_color = (1 - blendAmount) * grass + blendAmount * sand;
>>>>>>> parent of 98f534e... Adding .lib files, added the perlin seed being able to be changed using the GUI Bar
=======
		//out_color = (1 - blendAmount) * grass + blendAmount * sand;
		out_color = mix(grass, sand, 0.25);
>>>>>>> 9f15d9686915c53f8f70fe1cd0835ab9953780b5
	}
	else if(height > 0.58 && height < 0.65)
	{
		out_color = sand;
	}
	else if(height >= 0.52 && height <= 0.58)
	{
		out_color = mix(sand, water, 0.7);
	}
	else if(height < 0.52)
	{
		out_color = water;
	}

	// Final Colour
	out_color.a = 1;
	out_color = out_color * vec4( LightColour * d + LightColour * s, 1) * vec4(height, height, height, 1);
}