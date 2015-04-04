#version 410

in vec3 vNormal;
in vec4 vPosition;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

out vec4 FragColor;	

uniform sampler2D diffuse;
uniform sampler2D normal;	

uniform vec3 LightDir;
uniform vec3 LightPos;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform float SpecPow;

void main() 
{
	mat3 TBN = mat3( normalize(vTangent), normalize(vBiTangent), normalize(vNormal));

	vec3 N = texture(normal, vTexCoord).xyz * 2 - 1;
	
	vec3 lightDir = normalize(LightDir);
	
	float d = max(0.0, dot(normalize(TBN * N), lightDir ) );	
	
	//vec3 E = normalize( CameraPos - vPosition.xyz );
	
	//vec3 R = reflect( -lightDir, vNormal.xyz );
	
	//float s = max( 0, dot( E, R ) );
	
	//s = pow( s, SpecPow );	

	//float d = max(0, dot(normalize(TBN * N), normalize(lightDir)));

	vec3 E = normalize( CameraPos - vPosition.xyz );
	
	vec3 R = reflect( -lightDir, vNormal.xyz );

	float s = max( 0, dot( E, R ) );
	
	s = pow( s, SpecPow );

	FragColor = texture(diffuse, vTexCoord) * vec4( LightColour * d + LightColour * s, 1);//vec4(0.2,0.2,0.2,1); 

	//FragColor.rgb = FragColor.rgb * d;// = vec4( vNormal, 1);// LightColour * d + LightColour * s, 1);
};
