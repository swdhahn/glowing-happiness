/*
 * Model.h
 *
 *  Created on: Jun 11, 2020
 *      Author: Seth H.
 */

#ifndef RED_MODEL_H_
#define RED_MODEL_H_
#include "Maths.h"

namespace red {

class Model {
public:
	Model(red::Vector3 *vertices, int *indices, int verticesLength, int indicesLength);
	~Model();

public:
	red::Vector3 *vertices = nullptr;
	int *indices = nullptr;
	int verticesLength = -1, indicesLength = -1;
};

} /* namespace red */

#endif /* RED_MODEL_H_ */
