/*
 * Loader.h
 *
 *  Created on: Jun 11, 2020
 *      Author: Seth H.
 */

#ifndef LOADER_H_
#define LOADER_H_

#include <stdio.h>
#include <vector>
#include "Model.h"
#include "Maths.h"

namespace red {

Model loadModel(const char* path);

}

#endif /* LOADER_H_ */
