/*
 * ShaderProgram.cpp
 *
 *  Created on: 4 jun. 2020
 *      Author: Count
 */

#include "ShaderProgram.h"

red::ShaderProgram::ShaderProgram(red::Renderer * renderer) : renderer(renderer) {

}

red::ShaderProgram::~ShaderProgram() {

}

void red::ShaderProgram::drawTriangles(const int &color, const red::Matrix4 &proj, const red::Matrix4 &cam, const red::Vector4 *triangles, const int &count) {
	for(int i = 0; i < count; i ++) {
		red::Vector4 v1 = proj * cam * triangles[i * 3];
		red::Vector4 v2 = proj * cam * triangles[i * 3 + 1];
		red::Vector4 v3 = proj * cam * triangles[i * 3 + 2];
		renderer->drawTriangle(color, pointTo2dPlane(v1), pointTo2dPlane(v2), pointTo2dPlane(v3));
	}
}

red::Vector2 red::ShaderProgram::pointTo2dPlane(red::Vector4 point) {
	return red::Vector2((1 + point.x / point.w) / 2 * renderer->getWidth(), (1 + point.y / point.w) / 2 * renderer->getHeight());
}

