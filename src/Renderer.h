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
#include "Maths.h"

namespace red {

class Renderer {
public:
	const int IN_RANGE = 0;
	const int OUT_OF_RANGE = 1;

	Renderer(int width, int height);
	~Renderer();
	int Init(bool vsync);
	bool shouldWindowClose();
	void update();
	void destroyWindow();

	int drawPixel(const int color, const int &x, const int &y);
	int drawRectangle(const int &color, const int &x, const int &y, const int &width, const int &height);
	int fillRectangle(const int &color, const int &x, const int &y, const int &width, const int &height);
	int drawLine(const int &color, const int &x, const int &y, const int &x2, const int &y2);
	int drawTriangle(const int &color, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3);


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
