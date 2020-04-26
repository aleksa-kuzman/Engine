
g++ -g -I /usr/local/include -L /usr/local/lib  $(pkg-config --static --libs glfw3)  -ldl  triangle.cpp glad.c Shader.cpp stb_image.cpp loader.cpp -o triangle.out 



#-ldl -lpthread -lm  -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXinerama -lX11 -lXcursor 
