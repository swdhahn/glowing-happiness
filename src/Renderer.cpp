/*
 * Renderer.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"

red::Renderer::Renderer(int width, int height) :
		window(nullptr), width(width), height(height) {
	charPixels = new unsigned char[width * height * 3];
	pixels = new int[width * height];
}

red::Renderer::~Renderer() {
	glDeleteTextures(1, &texture);
	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	delete[] charPixels;
	delete[] pixels;
}

int red::Renderer::Init(bool vsync) {

	if (glfwInit() == GLFW_FALSE) {
		std::cout << "GLFW failed initialization!" << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "Engine From Scratch", NULL, NULL);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW failed initialization!" << std::endl;
		return -1;
	}

	//glViewport(0, 0, width, height);

	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!vsync)
		glfwSwapInterval(0);

	glfwSetWindowUserPointer(window, this);

	auto func = [](GLFWwindow *w, int x, int y) {
		static_cast<Renderer*>(glfwGetWindowUserPointer(w))->windowCallBack(w, x, y);
	};

	glfwSetWindowSizeCallback(window, func);

	/* not very important -- FROM HERE TO END */
	// Shader generation
	const char *vertexShaderSource = "#version 330 core\nlayout (location = 0) in vec3 aPos;\nout vec2 texCoords;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\ntexCoords = (aPos.xy + 1) * 0.5;\n}\0";
	const char *fragmentShaderSource = "#version 330 core\nout vec4 color;\nin vec2 texCoords;\nuniform sampler2D tex0;\nvoid main()\n{\ncolor = texture(tex0, texCoords);\n}\0";
	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
	tex0 = glGetUniformLocation(shaderProgram, "tex0");
	glUniform1i(tex0, 0);

	// Loading Data =
	float points[] = { -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f, -1.0f, 0.0f };

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(vao);

	// generating texture
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* END */
	return 1;
}

bool red::Renderer::shouldWindowClose() {
	return glfwWindowShouldClose(window);
}

void red::Renderer::update() {
	if(resetSizes) {
		charPixels = new unsigned char[width * height * 3];
		pixels = new int[width * height];
		this->width = width;
		this->height = height;
		resetSizes = false;
	}

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glActiveTexture(GL_TEXTURE0);

	int pptr = 0;
	for (int i = 0; i < width * height; i++) {
		charPixels[pptr++] = pixels[i] >> 16;
		charPixels[pptr++] = pixels[i] >> 8;
		charPixels[pptr++] = pixels[i];
		pixels[i] = 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &charPixels[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void red::Renderer::destroyWindow() {
	glfwDestroyWindow(window);
}

// RENDERING FUNCTIONS

int red::Renderer::drawPixel(const int color, const int &x, const int &y) {

	if (x < 0 || y < 0 || x >= width || y >= height)
		return OUT_OF_RANGE;

	// Alpha determination
	int prevColor = pixels[x + y * width];
	float alpha = -(float) (color >> 24);

	int r = ((color & 0x00FF0000) >> 16) * alpha + ((prevColor & 0x00FF0000) >> 16) * (1 - alpha);
	int g = ((color & 0x0000FF00) >> 8) * alpha + ((prevColor & 0x0000FF00) >> 8) * (1 - alpha);
	int b = (color & 0x000000FF) * alpha + (prevColor & 0x000000FF) * (1 - alpha);

	pixels[x + y * width] = (r << 16) + (g << 8) + b;

	return IN_RANGE;
}

int red::Renderer::fillRectangle(const int &color, const int &x, const int &y, const int &width, const int &height) {

	for (int i = 0; i < width * height; i++) {
		drawPixel(color, x + i % width, y + (i - i % width) / width + 1);
	}

	return IN_RANGE;
}

int red::Renderer::drawRectangle(const int &color, const int &x, const int &y, const int &width, const int &height) {

	for (int i = 0; i < width; i++) {
		drawPixel(color, x + i, y);
		drawPixel(color, x + i, y + height);
	}
	for (int j = 0; j < height; j++) {
		drawPixel(color, x, y + j);
		drawPixel(color, x + width, y + j);
	}

	return IN_RANGE;
}

int red::Renderer::drawTriangle(const int &color, const Vector2 &p1, const Vector2 &p2, const Vector2 &p3) {

	drawLine(color, p1.x, p1.y, p2.x, p2.y);
	drawLine(color, p2.x, p2.y, p3.x, p3.y);
	drawLine(color, p3.x, p3.y, p1.x, p1.y);

	return IN_RANGE;
}

int red::Renderer::drawLine(const int &color, const int &x, const int &y, const int &x2, const int &y2) {
	int startY = y, endY = y2;
	if (y > y2) {
		startY = y2;
		endY = y;
	}
	if ((x - x2) == 0) {
		for (int yy = startY; yy < endY; yy++) {
			drawPixel(color, x, yy);
		}
		return IN_RANGE;
	}
	float slope = (float) (y - y2) / (float) (x - x2);
	float yintercept = -slope * x + y;
	int startX = x, endX = x2;
	if (x > x2) {
		startX = x2;
		endX = x;
	}
	for (int xx = startX; xx < endX; xx++) {
		drawPixel(color, xx, slope * xx + yintercept);
	}
	for (int yy = startY; yy < endY; yy++) {
		drawPixel(color, (yy - yintercept) / slope, yy);
	}

	return IN_RANGE;
}

void red::Renderer::windowCallBack(GLFWwindow* w, int width, int height) {
	windowResized = true;
	resetSizes = true;
}

