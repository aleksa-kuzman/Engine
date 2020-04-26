#ifndef GAMEOBJECT_H
#define  GAMEOBJECT_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.cpp"
#include "stb_image.h"
#include "texture.cpp"

class GameObject
{
public:
    int attribPointerNum;
    int currentTexture;
    int vertexSize;
    int objectVertexSize;//kolika je velicina tacke koju trenutno hocemo da bindujemo sa shaderom
    int sizeofVertices; //kolika je tacna velicina onoga sto renderujemo
    int verticesAmount; // ukupan broj tacaka koje cine telo koje renderujemo
    Shader currentShader;

    Texture textures[4];
    int currentTex;

    unsigned int VBO, VAO;

    float vertices[10000];
    //unsigned int textures[];







    /*GameObject::attribPointerNum = 0;
    GameObject::currentTexture = 0;*/

    GameObject( float *vertices, int vertexSize,int objectVertexSize, int verticesAmount,int attribPointerNum,const char* vertex, const char* fragment ) :currentShader (vertex,fragment)

    {



        std::copy(vertices,vertices+vertexSize*verticesAmount *sizeof(float), this->vertices) ;
        this->vertexSize = vertexSize;
        this->sizeofVertices = vertexSize * verticesAmount * sizeof(float);
        this->verticesAmount = vertexSize * verticesAmount;
        this->objectVertexSize = objectVertexSize;
        this->attribPointerNum = attribPointerNum;
        this->currentTex = 0;
        glGenVertexArrays(1,&VAO);
        glGenBuffers (1,&VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,vertexSize *verticesAmount*sizeof(float),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(attribPointerNum,objectVertexSize, GL_FLOAT,GL_FALSE, vertexSize * sizeof(float),(void*)0 );
        glEnableVertexAttribArray(attribPointerNum);






    }

    void setAttribPointer(int pointer, int size,int index)
    {


        glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,vertexSize * sizeof(float),(void *) (pointer * sizeof(float ) ) ) ;
        glEnableVertexAttribArray(index);


    }


    void draw()
    {


        glDrawArrays(GL_TRIANGLES,0,verticesAmount);

    }

    void useShader()
    {

        currentShader.use();

    }





    void addTexture( char const *path,  char const * shaderUniform,int uniformNum, int startPoint,int index,int size)
    {
        Texture t (path);
        setAttribPointer(startPoint,size,index); //morace da se doda ova dvojka ovde kao parametar
        textures[currentTex] = t;




        currentShader.use();
        currentShader.setInt(shaderUniform,uniformNum);


        currentTex++;


    }


    ~GameObject()
    {
        glDeleteVertexArrays(1,&VAO);
        glDeleteBuffers(1,&VBO);



    }





};
#endif

