/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Seth H.
 */

#include "red/Renderer.h"
#include "red/ShaderProgram.h"
#include <inttypes.h>
#include <chrono>
#include <iostream>

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
	red::Quaternion rot, rot2;

	int frames = 0;
    float yyy = 0;
	auto start = getTime();
	while (!renderer->shouldWindowClose()) {

		rot2.fromAxis(red::Vector3(1, 0, 0), 3.14 * 1.05);
		camMatrix.toTransformationMatrix(red::Vector3(0, 6, 0 + 10), rot2, 1);
        yyy+=0.01;
        rot.fromAxis(red::Vector3(1, 1, 1), yyy);

		// render stuffs

		for (int i = -5; i < 6; i++) {
			for (int j = 1; j < 10; j++) {
				modelMatrix.toTransformationMatrix(red::Vector3(i, 4 + j / 2.0, 0 - j), rot, 0.5);
				shader.drawTriangles(0xFFFFFFFF, projectionMatrix, camMatrix, modelMatrix, vertices, 12);
			}
		}

		// end render stuffs

        if (renderer->windowResized) {
            projectionMatrix.toProjectionMatrix(renderer->getWidth(), renderer->getHeight(), 70, 1000, 0.5);
        }
		renderer->update();

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

