/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"
#include <chrono>

__int64 getTime();

red::Renderer *renderer;

void toScreen(red::Vector4 v, red::Vector2 &screenCoord) {

	screenCoord.x = (1 + v.x / v.w) / 2 * 640;
	screenCoord.y = (1 + v.y / v.w) / 2 * 360;
	std::cout << screenCoord.x << "  " << screenCoord.y << std::endl;
}

int main() {

	red::Vector4 vertices[] = { red::Vector4(-0.5, -0.5, -10, 1), red::Vector4(-0.5, 0.5, -10, 1), red::Vector4(0.5, 0.5, -10, 1) };

	renderer = new red::Renderer(640, 360);
	renderer->Init(false);

	int xxx = 0;

	red::Matrix4 projectionMatrix;
	projectionMatrix.toProjectionMatrix(640, 360, 70, 1000, 0.5);

	red::Vector2 v1(0, 0);
	red::Vector2 v2(0, 0);
	red::Vector2 v3(0, 0);
	toScreen(projectionMatrix * vertices[0], v1);
	toScreen(projectionMatrix * vertices[1], v2);
	toScreen(projectionMatrix * vertices[2], v3);

	int frames = 0;
	__int64 start = getTime();
	while (!renderer->shouldWindowClose()) {

		for (int i = 0; i < 100; i++) {
			renderer->drawTriangle(0xFFFF00FF, v1, v2, v3);
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

__int64 getTime() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

