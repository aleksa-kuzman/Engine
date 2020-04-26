#version 330 core

in vec2 TexCoords;
in vec3 Normals;
in vec3 FragPos;

uniform sampler2D modelTexture;
uniform vec3 lightColor;
uniform float shineDamper;
uniform vec3 lightPos;
uniform vec3 viewPos;



out vec4 FragColor;




void main()
{	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	
	vec3 norm = normalize (Normals);
	
	vec3 lightDir  = normalize (lightPos - FragPos);
	float diff = max(dot(norm,lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specStr = 1.f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),shineDamper);
	vec3 specular = specStr * spec * lightColor;

//	vec3 result = (ambient + diffuse + specular) *vec3(texture(modelTexture,TexCoords) );	
		
	FragColor = texture(modelTexture,TexCoords);
}
