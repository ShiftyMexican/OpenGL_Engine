#version 410

in vec4 frag_normal;
in vec2 frag_texcoord;
in vec4 frag_position;
in vec4 frag_tangent;
in vec4 frag_bitangent;
out vec4 FragColor;	

uniform sampler2D diffuse;
uniform sampler2D normal;	

uniform vec3 LightPos;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform float SpecPow;

void main() 
{
	mat3 TBN = mat3( normalize(frag_tangent), normalize(frag_bitangent), normalize(frag_normal));

	vec3 N = texture(normal, frag_texcoord).xyz * 2 - 1;
	
	vec3 lightDir = normalize(frag_position.xyz - LightPos);
	
	float d = max(0.0, dot(normalize(TBN * N), normalize(lightDir) ) );	
	
	vec3 E = normalize( CameraPos - frag_position.xyz );
	
	vec3 R = reflect( -lightDir, frag_normal.xyz );
	
	float s = max( 0, dot( E, R ) );
	
	s = pow( s, SpecPow );	

	FragColor = vec4(0.2,0.2,0.2,1); 
};
