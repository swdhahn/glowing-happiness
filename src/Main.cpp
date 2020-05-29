/*
 * Main.cpp
 *
 *  Created on: 20 may. 2020
 *      Author: Count
 */

#include "Renderer.h"

red::Renderer *renderer;

int main() {

	renderer = new red::Renderer(1280, 720);
	renderer->Init();

	while (!renderer->shouldWindowClose()) {

		renderer->update();
	}

	renderer->destroyWindow();

	delete renderer;

	return 1;
}

