#ifndef TERRAIN_H
#define TERRAIN_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <png.h>


#include "loader.h"


typedef struct int24 {

    unsigned int data : 24;

} int24;


class Terrain
{
private:
    constexpr	static  float SIZE = 800.f;
    float VERTEX_COUNT =0;
    constexpr 	static  float MAX_HEIGHT = 100;
    constexpr 	static  float MAX_PIXEL_COLOR =  256* 256;
    int sizeofIndicies;







    float x;
    float z;

    unsigned short **heightMap;
    int24 **height24Map;


public:
    Terrain(int gridX, int gridZ)
    {
        this->x = gridX * SIZE;
        this->z = gridZ * SIZE;

    }



    Loader *generateTerrain ()

    {

        if(	!LoadHeightMapFromPNG("res/Valley.png"))
            std::cout<<"nesto ne valja";


        sizeofIndicies = (int)(6 * (VERTEX_COUNT-1) * (VERTEX_COUNT -1)) *4;


        std::cout<<"sizeofIndicies: "<<sizeofIndicies<<std::endl;


        unsigned long long  count = VERTEX_COUNT * VERTEX_COUNT;

        float* vertices = new float [count * 3];
        float* normals = new float  [count *3];
        float* textureCoords = new float[ count *2];
        unsigned  int* indicies = new unsigned int [(int)(6 * (VERTEX_COUNT-1) * (VERTEX_COUNT -1)) ];
        unsigned long long vertexPointer = 0;
        for(int i = 0; i< VERTEX_COUNT; i++)
        {
            for(int j = 0; j < VERTEX_COUNT; j++)
            {

                vertices[vertexPointer *3] = (float)j/((float) VERTEX_COUNT-1)*SIZE;
                vertices[vertexPointer * 3+1] =getHeight(i,j,VERTEX_COUNT);


                vertices [vertexPointer * 3+2] = (float) i/( (float) VERTEX_COUNT -1 ) * SIZE;

                normals[vertexPointer * 3] = 0;
                normals[vertexPointer *3 +1] =1;
                normals[vertexPointer *3 +2] =0;

                textureCoords[vertexPointer *2] = (float) j/( (float) VERTEX_COUNT-1);
                textureCoords[vertexPointer *2+1] = (float) i/((float) VERTEX_COUNT - 1 );
                vertexPointer++;

            }




        }





        int pointer = 0;
        for(int gz=0; gz<VERTEX_COUNT-1; gz++)
        {
            for(int gx=0; gx<VERTEX_COUNT-1; gx++) {


                int topLeft = (gz * VERTEX_COUNT)+gx;
                int topRight = topLeft +1;
                int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
                int bottomRight = bottomLeft +1;

                indicies[pointer++] = topLeft;
                indicies[pointer++] = bottomLeft;
                indicies[pointer++] = topRight;
                indicies[pointer++] = topRight;
                indicies[pointer++] = bottomLeft;
                indicies[pointer++] = bottomRight;



            }


        }



        Vbo vbo1(vertices,count *12);
        Vbo vbo2(textureCoords,count *2 *4 );
        Vbo vbo3 (normals,count *3 *4);




        Loader* loader(new Loader() );

        loader->loadDataToVAO(vbo1,vbo2,vbo3,indicies, sizeofIndicies );



        return loader;



    }

    float getHeight(int x, int z,int height)
    {
        if(x <0 || x>= height|| z<0 || z>= height )
            return 0;

        float heightR= (float)heightMap[x][z];


        /*heightR += MAX_PIXEL_COLOR/2.f;
          heightR /= MAX_PIXEL_COLOR/2.f;
          heightR += 100;*/
        heightR /= MAX_HEIGHT;



        return heightR;

    }

    float get24Height(int x, int z, int height)
    {
        if(x <0 || x>= height|| z<0 || z>= height )
            return 0;

        float heightR= (float)heightMap[x][z];

        heightR /= MAX_HEIGHT;

        return heightR;



    }


    bool LoadHeightMap(char *fileName)
    {
        int width,height,nrChannels;
        int error,i,j,index;
        FILE * filePtr;
        unsigned long long imageSize, count;
        unsigned short* rawImage;
        rawImage = new unsigned short[(int)(this->x * this->z)];
        int24 *data;




        filePtr = fopen(fileName,"rb");

        fseek(filePtr,0,SEEK_END);
        imageSize = ftell(filePtr);
        rewind(filePtr);


        std::cout<<imageSize<<std::endl;
        data = new int24[imageSize/3];



        std::cout<<imageSize<<std::endl;

        fread(data,3,imageSize/3,filePtr);

        std::cout<<sizeof(imageSize)<<std::endl;


        VERTEX_COUNT = 960;

        long int s = 0;

        for(int i =0; i<960; i++)
        {
            for(int j=0; j< 960; j++)
            {

                height24Map[i][j] =( int24)data[s];
                s++;
            }

        }











        return true;







    }

    bool LoadHeightMapFromPNG(char *fileName)
    {
        int width,height,nrChannels;
        unsigned long long imageSize;
        unsigned short *data;


        data = stbi_load_16(fileName,&width,&height,&nrChannels,0);



        imageSize = width * height;

        VERTEX_COUNT = width;///4; //Moguce je da ce trebati u buducnosti



        for(int i=0; i< imageSize/4; i++)
            std::cout<<data[i]<<std::endl;
        /*

        				std::cout<<"width:"<<width<<"  height:" <<height <<std::endl;

        */


        heightMap = new unsigned short*[width];

        for(int i=0; i < width; i++)
            heightMap[i] = new unsigned short[height];


        long int s = 0;

        for(int i =0; i< width; i++)
        {
            for(int j=0; j< height ; j++)
            {
                /*unsigned short tmp = data[s] + data[s+1] + data[s+2]+ data[s+3];
                tmp/= 4;*/
                heightMap[i][j] =(unsigned short)data[s];
                s++;
            }

        }


        stbi_image_free(data);





        return true;








    }

    bool LoadHeightMapFromPNG_small(char *fileName)
    {
        int width,height,nrChannels;
        unsigned long long imageSize;
        unsigned short *data;


        data = stbi_load_16(fileName,&width,&height,&nrChannels,0);



        imageSize = width * height;

        VERTEX_COUNT = width/6; //Moguce je da ce trebati u buducnosti



        /*	for(int i=0; i< imageSize/4; i++)
        	std::cout<<data[i]<<std::endl;


        	std::cout<<"width:"<<width<<"  height:" <<height <<std::endl;

        */


        heightMap = new unsigned short*[width];

        for(int i=0; i < width/6; i++)
            heightMap[i] = new unsigned short[height];


        long int s = 0;

        for(int i =0; i< width/6; i++)
        {
            for(int j=0; j< height/6 ; j++)
            {
                unsigned short tmp = data[s] + data[s+1] + data[s+2] + data[s+3] +data[s+4] +data[s+5];
                tmp/= 6;
                heightMap[i][j] =(unsigned short)tmp;

                s+=6;

            }

        }


        stbi_image_free(data);





        return true;
    }


    int getSizeofIndicies()
    {
        return sizeofIndicies;
    }





};
#endif
