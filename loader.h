#ifndef LOADER_H
#define LOADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "VBO.cpp"


class Loader
{
	private:

	unsigned int VAO;
	unsigned int VBO1,VBO2,VBO3,EBO;
	
	//Vbo VBO1,VBO2;


	public:

	Loader( )
	{
		VAO = 0;
		VBO1,VBO2,VBO3,EBO = 0;

	/*	glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&VBO1);
		glGenBuffers(1,&VBO2);
		glGenBuffers(1,&EBO);


		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER,VBO1);
		glBufferData(GL_ARRAY_BUFFER,48,vertices,GL_STATIC_DRAW);
		
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *) 0);
		glEnableVertexAttribArray(0);



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,24,indicies,GL_STATIC_DRAW);

		
		glBindBuffer(GL_ARRAY_BUFFER,VBO2);
		glBufferData(GL_ARRAY_BUFFER,48,colors,GL_STATIC_DRAW);
		

		glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float), (void *) 0);
		glEnableVertexAttribArray(1);

	
		


	//	std::cout<<(sizeof(float) );
*/
	}
	void loadDataToVAO (Vbo & vertices, Vbo& colors, Vbo& normals, unsigned int * indicies,int sizeOfIndicies )

	{
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&EBO);

		glBindVertexArray(VAO);


		glBindBuffer(GL_ARRAY_BUFFER,vertices.get_ID());
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *) 0 );
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER,colors.get_ID());
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void *) 0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER,normals.get_ID());
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,3*sizeof(float), (void*) 0);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeOfIndicies,indicies,GL_STATIC_DRAW);

		
		

	
	}

	void loadDataToVAO(Vbo & vertices,unsigned int* indicies,int sizeOfIndicies)
	{
		glGenVertexArrays(1,&VAO);
		glGenBuffers(1,&EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER,vertices.get_ID());
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void *) 0 );
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeOfIndicies,indicies,GL_STATIC_DRAW);



	
	}

	void bindVAO()
	{
		glBindVertexArray(VAO);
	
	}


	



};
#endif
