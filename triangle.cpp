#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <math.h>
#include "Shader.cpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "gameObject.cpp"
#include "loader.cpp"
#include "VBO.cpp"
#include "terrain.h"


void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void processInput(GLFWwindow *window);


glm::vec3 cameraPos = glm::vec3(55.f,0.f,35.f);
glm::vec3 cameraFront = glm::vec3(0.f,0.f,-1.f);
glm::vec3 cameraUp = glm::vec3(0.f,1.f,0.f);

float deltaTime = 0.f;
float lastFrame = 0.f;

float yaw =-90.f;
float pitch = 0.f;
float lastX= 800.f /2;
float lastY= 600.f /2;

bool firstMouse =true;


float fov =45.f;

float angle = 1.f;


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


const int TERRAIN_WIDTH = 512;
const int TERRAIN_DEPTH = 512;
const int TERRAIN_HALF_WIDTH = TERRAIN_WIDTH>>1;
const int TERRAIN_HALF_DEPTH = TERRAIN_DEPTH>>1;

float scale = 50;
float half_scale = scale/2.0f;

const int TOTAL = TERRAIN_WIDTH * TERRAIN_DEPTH;
const int TOTAL_INDICIES = TOTAL * 2 * 3;

glm::vec3 vertices[TOTAL];
unsigned int indicies[TOTAL_INDICIES];

int main (){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800,600,"Engine",NULL,NULL);

	if(window == NULL)
	{
		std::cout << "Neuspesno generisan prozor" <<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		std::cout <<"GLAD nije uspesno ucitan" <<std::endl;
		return -1;
	}

	float degreeAngle = 45;
	glViewport(0,0,800,600);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
//	glfwSetKeyCallback(window,key_callback);
	glfwSetWindowUserPointer(window,&degreeAngle);
	glfwSetCursorPosCallback(window,mouse_callback);

	Shader shader ("lightingShader.vs","lightingShader.fs");
	shader.use();

	shader.setiVec2("HALF_TERRAIN_SIZE",TERRAIN_WIDTH>>1,TERRAIN_DEPTH>>1);
	shader.setFloat("scale",scale);
	shader.setFloat("half_scale",half_scale);



	
	
/*
float vertices [] = {

	.5f,.5f,0.f,
	.5f,-.5f,0.f,
	-.5f,-.5f,0.f,
	-.5f,.5f,0.f	


	};

	float normals [] = {
	
	
		1.f,1.f,1.f,
		1.f,0.f,2.f,
		0.f,0.f,3.f,
		0.f,1.f,4.f
	

	};

	unsigned int indicies []  {
	
	0,1,3,
	1,2,3


	};

	float colors []  {
	
	
	
	
		1.f,1.f,
		1.f,0.f,
		0.f,0.f,
		0.f,1.f


	};

*/



	/*unsigned int VAO,VBO,EBO,VBO2;

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	glGenBuffers(1,&VBO2);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indicies),indicies,GL_STATIC_DRAW);




	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*) 0);
	glEnableVertexAttribArray(0);
	

	glBindBuffer(GL_ARRAY_BUFFER,VBO2);
	glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)  0 );
	glEnableVertexAttribArray(1);
	

	std::cout<<VAO;
*/
	//std::cout<<sizeof(vertices);


//	Vbo VBO1 (vertices,sizeof(vertices) );
//	Vbo VBO2 (colors,sizeof(colors) );
//	Vbo VBO3 (normals,sizeof(normals));

	Texture texture1("res/trava.png");

//	Loader loader ( VBO1,VBO2,VBO3,indicies);
//


	Terrain teren (1,1);	
	Loader* loader = teren.generateTerrain();





//	Loader loader;
//	loader.loadDataToVAO(VBO1,VBO2,VBO3,indicies,sizeof(indicies));
	

 
	



		

	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
	
		deltaTime = currentFrame - lastFrame;
		
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		
	//	texture1.bindTexture(1);

		float ugao = (float)( glfwGetTime());
		
		shader.use();
		//projection
		glm::mat4 projection = glm::perspective(glm::radians(fov),(float)SCR_WIDTH / (float) SCR_HEIGHT,0.1f,5000.f);
		shader.setMat4("projectionMatrix",projection);
		//view
	
		//model
		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::rotate(model,glm::radians(40.f), glm::vec3(0.f,1.f,0.f));
		
		glm::mat4 view = glm::lookAt(cameraPos,cameraPos+ cameraFront,cameraUp);
		shader.setMat4("viewMatrix",view);

		model = glm::translate(model,glm::vec3(0.f,-60.f,0.f));

		shader.setMat4("modelMatrix",model);
	
		loader->bindVAO();
		glDrawElements(GL_TRIANGLES,teren.getSizeofIndicies(),GL_UNSIGNED_INT,0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}




void processInput(GLFWwindow *window)
{

	
	float cameraSpeed = 100 * deltaTime;
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);

	if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)	
	cameraPos -= cameraSpeed * cameraFront;

	

	if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront,cameraUp) ) * cameraSpeed;

	if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront,cameraUp) ) * cameraSpeed;
	
	if(glfwGetKey(window,GLFW_KEY_H) == GLFW_PRESS)
		std::cout<< 1/deltaTime<<std::endl;
		
		
		//std::cout<< cameraPos.x <<"  "<< cameraPos.y<<"   " << cameraPos.z<<std::endl;


}

void mouse_callback(GLFWwindow * window, double xpos,double ypos)
{
		//std::cout<<xpos <<std::endl;
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;

		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.01f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch +=yoffset;

	if(pitch > 89.f)
		pitch = 89.f;
	if(pitch < -89.f)
		pitch = -89.f;

	glm::vec3 front;

	front.x = cos(glm::radians(yaw) ) * cos(glm::radians(pitch) ) ;
	front.y = sin(glm::radians(pitch ) );
	front.z = sin(glm::radians(yaw) ) * cos(glm::radians(pitch) ) ;

	cameraFront = glm::normalize(front);

}

void framebuffer_size_callback(GLFWwindow * window,int width,int height)
{
	glViewport(0,0,width,height);
}




