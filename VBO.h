#ifndef VBO_H
#define VBO_H


#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Vbo
{

	private:
	unsigned int ID;
	unsigned int size;

	public:

	Vbo ( float * vertices, unsigned int size)
	{
		this->size = size;
		glGenBuffers(1,&ID);
		glBindBuffer(GL_ARRAY_BUFFER,ID);
		glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STREAM_DRAW);
	}

	Vbo(glm::vec3 *vertices, unsigned int size)
	{
	
	this->size = size;
		glGenBuffers(1,&ID);
		glBindBuffer(GL_ARRAY_BUFFER,ID);
		glBufferData(GL_ARRAY_BUFFER,size,vertices,GL_STREAM_DRAW);

	}


	unsigned int get_ID()
	{
		return ID;
	}
		




};
#endif
