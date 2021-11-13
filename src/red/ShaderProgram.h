/*
 * ShaderProgram.h
 *
 *  Created on: 4 jun. 2020
 *      Author: Seth H.
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "Maths.h"
#include "Renderer.h"

namespace red {
class ShaderProgram {
public:
	ShaderProgram(red::Renderer *renderer);
	~ShaderProgram();
	void drawTriangles(const int &color, const red::Matrix4 &proj, const red::Matrix4 &cam, const red::Matrix4 &model, const red::Vector4 *triangles, const int &count);

public:
	red::Renderer *renderer = nullptr;

private:
	red::Vector2 pointTo2dPlane(red::Vector4 point);
};
}

#endif /* SHADERPROGRAM_H_ */
