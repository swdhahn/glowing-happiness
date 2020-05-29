/*
 * Renderer.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"

red::Renderer::Renderer(unsigned int width, unsigned int height) :
		window(nullptr), width(width), height(height) {
	charPixels = new unsigned char[width * height * 3];
	pixels = new int[width * height];
}

red::Renderer::~Renderer() {

}

int red::Renderer::Init() {

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
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glActiveTexture(GL_TEXTURE0);

	for(int y = 0; y < 200; y++) {
		for(int x = 0; x < 100; x++) {

			pixels[x + y * width] = 0xFFFF66;
		}
	}

	int pptr = 0;
	for(int i = 0; i < width * height; i ++) {
		charPixels[pptr++] = pixels[i] >> 16;
		charPixels[pptr++] = pixels[i] >> 8;
		charPixels[pptr++] = pixels[i];
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &charPixels[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glfwPollEvents();
	glfwSwapBuffers(window);
	for(int i = 0; i < width * height; i ++) {
		pixels[i] = 0;
	}
}

void red::Renderer::destroyWindow() {
	glfwDestroyWindow(window);
}

