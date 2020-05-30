/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"
#include <chrono>

red::Renderer *renderer;

int main() {

	renderer = new red::Renderer(1280, 720);
	renderer->Init(true);

	int xxx = 0;

	int frames = 0;
	__int64 start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	while (!renderer->shouldWindowClose()) {

		renderer->drawRectangle(0xFFFFFFFF, xxx, 100, 20, 50);
		renderer->drawLine(0xFFFF00FF, 200, 200, 250, 100);

		renderer->update();
		xxx++;

		frames ++;
		if(start + 1000 < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) {
			std::cout << "Fps: " << frames << std::endl;
			frames = 0;
			start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		}
	}

	renderer->destroyWindow();

	delete renderer;

	return 1;
}

