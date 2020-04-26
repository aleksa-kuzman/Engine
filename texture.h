
#ifndef TEXTURE_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.cpp"
#include "stb_image.h"

class Texture
{

	public:
	unsigned int textureID;
	int width,height,nrChannels;
	unsigned char *data;


	Texture(){
	 this->textureID = 100;
	
	}

	Texture( char const *path){

		glGenTextures(1, &textureID);

		std::cout<<" -->" << textureID << std::endl;

		data = stbi_load(path,&width,&height,&nrChannels,0);
		if(data)
		{
			GLenum format;
			if(nrChannels == 1)
				format = GL_RED;
			else if(nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;
			
			//stbi_set_flip_vertically_on_load(true);

			glBindTexture(GL_TEXTURE_2D,textureID);
			glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
			std::cout << "Tekstura uspesno ucitana"<< std::endl;
		}
		else
		{
			std::cout<<"Tekstura nije uspesno ucitana na putanji: " << path << std::endl;
			stbi_image_free(data);
		}
	
	
	}

	void bindTexture(int number){

		/*ako zelimo da kombinujemo teksture u funkciji glActiveTexture cemo birati drugaciji
		 GLenum (GL_TEXTURE0,GL_TEXTURE1 itd... )*/

		switch(number){
		case 0:
			glActiveTexture(GL_TEXTURE0);
			break;
		case 1:
			glActiveTexture(GL_TEXTURE1);
			break;
		case 2:
			glActiveTexture(GL_TEXTURE2);
			break;
		case 3: 
			glActiveTexture(GL_TEXTURE3);
			


		glBindTexture(GL_TEXTURE_2D,textureID);

		}
	



	}

	void loadHeightMap( const char* path)
	{
		
		data = stbi_load(path,&width,&height,&nrChannels,0);

		if(data)
		{
				GLenum format;
			if(nrChannels == 1)
				format = GL_RED;
			else if(nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;


		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1,&textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,textureID);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		
		
		glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE, data);



		



		}

	}




};
#endif

