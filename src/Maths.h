/*
 * Maths.h
 *
 *  Created on: 30 may. 2020
 *      Author: Count
 */

#ifndef MATHS_H_
#define MATHS_H_

#include <cmath>
#include <iostream>

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

#define VECTOR3_X Vector3(1, 0, 0)
#define VECTOR3_Y Vector3(0, 1, 0)
#define VECTOR3_Z Vector3(0, 0, 1)

class Vector3 {
public:
	float x, y, z;
	Vector3(float x, float y, float z);
	Vector3();

	void normalize();
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
	//Rows then columns; y then x
	float **m = nullptr;
	Matrix3();
	Matrix3(float *mat[3]);
	~Matrix3();

	void setIdentity();
	void clearMatrix();

	Vector3 operator * (const Vector3 &v);
	Matrix3 operator * (const Matrix3 &v);

};

class Quaternion;

class Matrix4 {
public:
	//Rows then columns; y then x
	float **m = nullptr;
	Matrix4();
	Matrix4(float *mat[4]);
	~Matrix4();

	void setIdentity();
	void clearMatrix();
	void setValues(float**v);
	void toProjectionMatrix(float width, float height, float FOV, float zFar, float zNear);
	void toTransformationMatrix(const Vector3 &position, Quaternion &quat, const float &scale);
	void toTransformationMatrix(const Vector3 &position, Quaternion &quat, const Vector3 &scale);
	void translate(const Vector3 &v);
	void setTranslation(const Vector3 &v);
	void scale(const Vector3 &v);
	void scale(const float &v);
	void rotate(const Quaternion &v);

	Vector4 operator * (const Vector4 &v) const;
	Matrix4 operator * (const Matrix4 &v) const;

};

class Quaternion {
public:
	float x, y, z, w;

	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector3 &axis, float rot);

	void createMatrix4(Matrix4 &matrix) const;
	void createMatrix3(Matrix3 &matrix);
	void fromAxis(const Vector3 &v, float angle);
	void normalize(Quaternion &v) const;

	Quaternion operator*(const Quaternion &v);
};

Matrix4 multiplyTwoMatricies(const Matrix4 &m1, const Matrix4 &m2);


}

#endif /* MATHS_H_ */
