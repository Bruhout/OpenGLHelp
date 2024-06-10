CC = g++
CFLAGS = -g -Wall
LFLAGS = -lglfw -lGL -lGLU -lglut

transform: src/transform.cpp glad.o shaderClass.o textureClass.o shaders/vertex.shader shaders/fragment.shader
	$(CC) -o transform src/transform.cpp glad.o shaderClass.o textureClass.o $(LFLAGS) $(CFLAGS)

glad.o: /usr/include/glad/glad.c
	$(CC) -o glad.o -c /usr/include/glad/glad.c $(CFLAGS) $(LFLAGS)

shaderClass.o: src/shaderClass.cpp
	$(CC) -o shaderClass.o src/shaderClass.cpp -c $(CFLAGS) $(LFLAGS)

textureClass.o: src/textureClass.cpp
	$(CC) -o textureClass.o src/textureClass.cpp -c $(CFLAGS) $(LFLAGS)
