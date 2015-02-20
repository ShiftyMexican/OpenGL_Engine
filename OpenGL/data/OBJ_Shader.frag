#version 410

in vec3 vNormal;
in vec2 vTexCoord;
in vec4 vPosition;
out vec4 FragColor;	
uniform sampler2D diffuse;	

uniform vec3 LightPos;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform float SpecPow;

void main() 
{
	vec3 lightDir = normalize(vPosition.xyz - LightPos);
	
	float d = max(0.0,dot(normalize(vNormal.xyz), -lightDir ) );	
	
	vec3 E = normalize( CameraPos - vPosition.xyz );
	
	vec3 R = reflect( -lightDir, vNormal.xyz );
	
	float s = max( 0, dot( E, R ) );
	
	s = pow( s, SpecPow );	
	
	FragColor = texture(diffuse, vTexCoord) * vec4(LightColour * d + LightColour * s, 1); 
};
