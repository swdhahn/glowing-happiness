/*
 * Renderer.h
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#define GLFW_DLL
#define GLEW_DLL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace red {

class Renderer {
public:
	Renderer(unsigned int width, unsigned int height);
	~Renderer();
	int Init();
	bool shouldWindowClose();
	void update();
	void destroyWindow();



private:
	GLFWwindow *window = nullptr;
	GLuint shaderProgram = -1;
	GLuint vbo = -1;
	GLuint vao = -1;
	GLuint tex0 = -1;
	GLuint texture = -1;
	unsigned char *charPixels = nullptr;
	int *pixels = nullptr;
	int width = -1;
	int height = -1;
};

}

#endif /* RENDERER_H_ */
