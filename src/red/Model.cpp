/*
 * Model.cpp
 *
 *  Created on: Jun 11, 2020
 *      Author: Seth H.
 */

#include "Model.h"

namespace red {

Model::Model(red::Vector3 *vertices, int *indices, int verticesLength, int indicesLength) :
		vertices(vertices), indices(indices), verticesLength(verticesLength), indicesLength(indicesLength) {
}

Model::~Model() {
	delete[] vertices;
	delete[] indices;
}

} /* namespace red */
