/*
 * Maths.h
 *
 *  Created on: 30 may. 2020
 *      Author: Count
 */

#ifndef MATHS_H_
#define MATHS_H_

#include <cmath>

namespace red {

class Vector2 {
public:
	float x, y;
	Vector2(float x, float y);
	Vector2();

	void normalize(Vector2 &v);

	Vector2 operator + (const red::Vector2 &v2);
	Vector2 operator - (const red::Vector2 &v2);
	Vector2 operator + (const float &v2);
	Vector2 operator - (const float &v2);
	Vector2 operator * (const float &scalar);
};

class Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z);
	Vector3();

	void normalize(Vector3 &v);
	float dot(const Vector3 &v);
	Vector3 cross(const Vector3 &v);

	Vector3 operator + (const red::Vector3 &v2);
	Vector3 operator - (const red::Vector3 &v2);
	Vector3 operator + (const float &v2);
	Vector3 operator - (const float &v2);
	Vector3 operator * (const float &scalar);
};

class Vector4 {
public:
	float x, y, z, w;
	Vector4(float x, float y, float z, float w);
	Vector4();

	void normalize(Vector4 &v);
	float dot(const Vector4 &v);
	Vector4 cross(const Vector4 &v);

	Vector4 operator + (const red::Vector4 &v2);
	Vector4 operator - (const red::Vector4 &v2);
	Vector4 operator + (const float &v2);
	Vector4 operator - (const float &v2);
	Vector4 operator * (const float &scalar);
};

class Matrix3 {
public:
	//Columns then rows
	float m[][] = new float[3][3];

	Vector4 operator * (const Vector4 &v);
};



}

#endif /* MATHS_H_ */
