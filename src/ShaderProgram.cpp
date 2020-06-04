/*
 * ShaderProgram.cpp
 *
 *  Created on: 4 jun. 2020
 *      Author: Count
 */

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(red::Renderer * renderer) : renderer(renderer) {

}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::drawTriangles(const int &color, const red::Matrix4 &proj, const red::Matrix4 &cam, const red::Vector2 *triangles, const int &count) {
	for(int i = 0; i < count; i ++) {
		renderer->drawTriangle(color, triangles[i * 3], triangles[i * 3 + 1], triangles[i * 3 + 2]);
	}
}

