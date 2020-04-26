#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aColor;
layout (location = 2) in vec3 aNormals;

out vec2 TexCoords;
out vec3 Normals;
out vec3 FragPos;

out vec3 viewPos;


uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPos;


void main()
{


	FragPos = vec3(modelMatrix * (vec4(aPos,1.0) ));
	TexCoords = aColor * 40.f;
	Normals = mat3(transpose(inverse(modelMatrix ) ) ) * aNormals;

	gl_Position = projectionMatrix * viewMatrix* modelMatrix *vec4(FragPos,1.0);


      
}
