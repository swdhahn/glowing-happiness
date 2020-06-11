/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "red/Renderer.h"
#include "red/ShaderProgram.h"
#include <inttypes.h>
#include <chrono>

int64_t getTime();

red::Renderer *renderer;

int main() {

	red::Vector4 vertices[] = {
	//+z
			red::Vector4(-0.5, -0.5, 0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(-0.5, 0.5, 0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(0.5, 0.5, 0.5, 1), red::Vector4(-0.5, 0.5, 0.5, 1),
			//-z
			red::Vector4(-0.5, -0.5, -0.5, 1), red::Vector4(0.5, -0.5, -0.5, 1), red::Vector4(-0.5, 0.5, -0.5, 1), red::Vector4(0.5, -0.5, -0.5, 1), red::Vector4(0.5, 0.5, -0.5, 1), red::Vector4(-0.5, 0.5, -0.5, 1),
			//top
			red::Vector4(0.5, 0.5, -0.5, 1), red::Vector4(0.5, 0.5, 0.5, 1), red::Vector4(-0.5, 0.5, 0.5, 1), red::Vector4(0.5, 0.5, -0.5, 1), red::Vector4(0.5, 0.5, 0.5, 1), red::Vector4(-0.5, 0.5, 0.5, 1),
			//bottom
			red::Vector4(0.5, -0.5, -0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(-0.5, -0.5, 0.5, 1), red::Vector4(0.5, -0.5, -0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(-0.5, -0.5, 0.5, 1),
			//-x
			red::Vector4(-0.5, -0.5, -0.5, 1), red::Vector4(-0.5, -0.5, 0.5, 1), red::Vector4(-0.5, 0.5, -0.5, 1), red::Vector4(-0.5, -0.5, 0.5, 1), red::Vector4(-0.5, 0.5, 0.5, 1), red::Vector4(-0.5, 0.5, -0.5, 1),
			//+x
			red::Vector4(0.5, -0.5, -0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(0.5, 0.5, -0.5, 1), red::Vector4(0.5, -0.5, 0.5, 1), red::Vector4(0.5, 0.5, 0.5, 1), red::Vector4(0.5, 0.5, -0.5, 1) };

	renderer = new red::Renderer(1280, 720);
	renderer->Init(false);
	red::ShaderProgram shader(renderer);

	int xxx = 1;

	red::Matrix4 projectionMatrix;
	projectionMatrix.toProjectionMatrix(renderer->getWidth(), renderer->getHeight(), 70, 1000, 0.5);
	red::Matrix4 camMatrix, modelMatrix;
	red::Quaternion rot;

	int frames = 0;
	auto start = getTime();
	while (!renderer->shouldWindowClose()) {

		rot.fromAxis(red::Vector3(0, 1, 0), xxx / 100.0);
		camMatrix.toTransformationMatrix(red::Vector3(0, 0, -5), rot, 1);

		shader.drawTriangles(0xFFFF00FF, projectionMatrix, camMatrix, modelMatrix, vertices, 12);

		renderer->update();

		if (renderer->windowResized) {
			projectionMatrix.toProjectionMatrix(renderer->getWidth(), renderer->getHeight(), 70, 1000, 0.5);
			renderer->windowResized = false;
		}
		xxx++;

		frames++;
		if (start + 1000 < getTime()) {
			std::cout << "Fps: " << frames << std::endl;
			frames = 0;
			start = getTime();
		}
	}

	renderer->destroyWindow();

	delete renderer;

	return 1;
}

int64_t getTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

