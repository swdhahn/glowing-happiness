/*
 * ShaderProgram.h
 *
 *  Created on: 4 jun. 2020
 *      Author: Count
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "Maths.h"
#include "Renderer.h"

namespace {
class ShaderProgram {
public:
	ShaderProgram(red::Renderer *renderer);
	~ShaderProgram();
	void drawTriangles(const int &color, const red::Matrix4 &proj, const red::Matrix4 &cam, const red::Vector2 *triangles, const int &count);

public:
	red::Renderer *renderer = nullptr;

};
}

#endif /* SHADERPROGRAM_H_ */
