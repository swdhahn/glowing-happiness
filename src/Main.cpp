/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"
#include "ShaderProgram.h"
#include <chrono>

__int64 getTime();

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
	red::Matrix4 camMatrix;
	red::Quaternion rot;

	int frames = 0;
	__int64 start = getTime();
	while (!renderer->shouldWindowClose()) {

		rot.fromAxis(red::Vector3(0, 1, 0), xxx / 100.0);
		camMatrix.toTransformationMatrix(red::Vector3(0, 0, -10 - xxx), rot, 0.2);

		shader.drawTriangles(0xFFFF00FF, projectionMatrix, camMatrix, vertices, 12);

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

__int64 getTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

