/*
 * Maths.cpp
 *
 *  Created on: 30 may. 2020
 *      Author: Count
 */

#include "Maths.h"

// VECTOR 2 ##########################################################################

red::Vector2::Vector2(float x, float y) :
		x(x), y(y) {
}

red::Vector2::Vector2() :
		x(0), y(0) {
}

void red::Vector2::normalize(red::Vector2 &v) {
	int d = sqrt(v.x * v.x + v.y * v.y);
	v.x /= d;
	v.y /= d;
}

red::Vector2 red::Vector2::operator +(const red::Vector2 &v2) {
	return red::Vector2(x + v2.x, y + v2.y);
}

red::Vector2 red::Vector2::operator -(const red::Vector2 &v2) {
	return red::Vector2(x - v2.x, y - v2.y);
}

red::Vector2 red::Vector2::operator +(const float &v2) {
	return red::Vector2(x + v2, y + v2);
}

red::Vector2 red::Vector2::operator -(const float &v2) {
	return red::Vector2(x - v2, y - v2);
}

red::Vector2 red::Vector2::operator *(const float &scalar) {
	return red::Vector2(x * scalar, y * scalar);
}

// VECTOR 3 ##########################################################################

red::Vector3::Vector3(float x, float y, float z) :
		x(x), y(y), z(z) {
}

red::Vector3::Vector3() :
		x(0), y(0), z(0) {
}

void red::Vector3::normalize() {
	int d = sqrt(x * x + y * y + z * z);
	x /= d;
	y /= d;
	z /= d;
}

float red::Vector3::dot(const red::Vector3 &v) {
	return x * v.x + y * v.y + z * v.z;
}

red::Vector3 red::Vector3::cross(const red::Vector3 &v) {
	return red::Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

red::Vector3 red::Vector3::operator +(const red::Vector3 &v2) {
	return Vector3(x + v2.x, y + v2.y, z + v2.y);
}

red::Vector3 red::Vector3::operator -(const red::Vector3 &v2) {
	return Vector3(x - v2.x, y - v2.y, z - v2.y);
}

red::Vector3 red::Vector3::operator +(const float &v2) {
	return Vector3(x + v2, y + v2, z + v2);
}

red::Vector3 red::Vector3::operator -(const float &v2) {
	return Vector3(x - v2, y - v2, z - v2);
}

red::Vector3 red::Vector3::operator *(const float &scalar) {
	return red::Vector3(x * scalar, y * scalar, z * scalar);
}

// VECTOR 4 ##########################################################################

red::Vector4::Vector4(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w) {
}

red::Vector4::Vector4() :
		x(0), y(0), z(0), w(0) {
}

void red::Vector4::normalize(Vector4 &v) {
	int d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= d;
	v.y /= d;
	v.z /= d;
}

float red::Vector4::dot(const red::Vector4 &v) {
	return x * v.x + y * v.y + z * v.z;
}

red::Vector4 red::Vector4::cross(const red::Vector4 &v) {
	return red::Vector4(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, 1);
}

red::Vector4 red::Vector4::operator +(const red::Vector4 &v2) {
	return red::Vector4(x + v2.x, y + v2.y, z + v2.y, w + v2.w);
}

red::Vector4 red::Vector4::operator -(const red::Vector4 &v2) {
	return red::Vector4(x - v2.x, y - v2.y, z - v2.y, w - v2.w);
}

red::Vector4 red::Vector4::operator +(const float &v2) {
	return red::Vector4(x + v2, y + v2, z + v2, w + v2);
}

red::Vector4 red::Vector4::operator -(const float &v2) {
	return red::Vector4(x - v2, y - v2, z - v2, w - v2);
}

red::Vector4 red::Vector4::operator *(const float &scalar) {
	return red::Vector4(x * scalar, y * scalar, z * scalar, w);
}

// MATRIX 3 ##########################################################################

red::Matrix3::Matrix3() {
	m = new float*[3];
	m[0] = new float[3];
	m[1] = new float[3];
	m[2] = new float[3];
}

red::Matrix3::Matrix3(float *mat[3]) :
		m(mat) {

}

red::Matrix3::~Matrix3() {
	delete[] m[0];
	delete[] m[1];
	delete[] m[2];
	delete[] m;
}

void red::Matrix3::setIdentity() {
	clearMatrix();
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
}

void red::Matrix3::clearMatrix() {
	for (int i = 0; i < 3; i++) {
		m[i][0] = 0;
		m[i][1] = 0;
		m[i][2] = 0;
	}
}

red::Vector3 red::Matrix3::operator *(const red::Vector3 &v) {
	return red::Vector3(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z, m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z, m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
}

red::Matrix3 red::Matrix3::operator *(const red::Matrix3 &v) {
	float **mm = new float*[3];
	mm[0] = new float[3];
	mm[1] = new float[3];
	mm[2] = new float[3];

	mm[0][0] = m[0][0] * v.m[0][0] + m[0][1] * v.m[1][0] + m[0][2] * v.m[2][0];
	mm[0][1] = m[0][0] * v.m[0][1] + m[0][1] * v.m[1][1] + m[0][2] * v.m[2][1];
	mm[0][2] = m[0][0] * v.m[0][2] + m[0][1] * v.m[1][2] + m[0][2] * v.m[2][2];

	mm[1][0] = m[1][0] * v.m[0][0] + m[1][1] * v.m[1][0] + m[1][2] * v.m[2][0];
	mm[1][1] = m[1][0] * v.m[0][1] + m[1][1] * v.m[1][1] + m[1][2] * v.m[2][1];
	mm[1][2] = m[1][0] * v.m[0][2] + m[1][1] * v.m[1][2] + m[1][2] * v.m[2][2];

	mm[2][0] = m[2][0] * v.m[0][0] + m[2][1] * v.m[1][0] + m[2][2] * v.m[2][0];
	mm[2][1] = m[2][0] * v.m[0][1] + m[2][1] * v.m[1][1] + m[2][2] * v.m[2][1];
	mm[2][2] = m[2][0] * v.m[0][2] + m[2][1] * v.m[1][2] + m[2][2] * v.m[2][2];

	return red::Matrix3(mm);
}

// MATRIX 4 ##########################################################################

red::Matrix4::Matrix4() {
	m = new float*[4];
	m[0] = new float[4];
	m[1] = new float[4];
	m[2] = new float[4];
	m[3] = new float[4];
}

// MUST BE CREATED WITH NEW KEYWORD
red::Matrix4::Matrix4(float **mat) :
		m(mat) {
}

red::Matrix4::~Matrix4() {
	delete[] m[0];
	delete[] m[1];
	delete[] m[2];
	delete[] m[3];
	delete[] m;
}

void red::Matrix4::translate(const red::Vector3 &v) {
	m[3][0] = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
	m[3][1] = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
	m[3][2] = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
	m[3][3] = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z;
}

void red::Matrix4::setTranslation(const red::Vector3 &v) {
	m[3][0] = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
	m[3][1] = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
	m[3][2] = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
	m[3][3] = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z;
}

void red::Matrix4::scale(const red::Vector3 &v) {
	m[0][0] = m[0][0] * v.x;
	m[0][1] = m[0][1] * v.x;
	m[0][2] = m[0][2] * v.x;
	m[0][3] = m[0][3] * v.x;

	m[1][0] = m[1][0] * v.y;
	m[1][1] = m[1][1] * v.y;
	m[1][2] = m[1][2] * v.y;
	m[1][3] = m[1][3] * v.y;

	m[2][0] = m[2][0] * v.z;
	m[2][1] = m[2][1] * v.z;
	m[2][2] = m[2][2] * v.z;
	m[2][3] = m[2][3] * v.z;
}

void red::Matrix4::scale(const float &v) {
	m[0][0] = m[0][0] * v;
	m[0][1] = m[0][1] * v;
	m[0][2] = m[0][2] * v;
	m[0][3] = m[0][3] * v;

	m[1][0] = m[1][0] * v;
	m[1][1] = m[1][1] * v;
	m[1][2] = m[1][2] * v;
	m[1][3] = m[1][3] * v;

	m[2][0] = m[2][0] * v;
	m[2][1] = m[2][1] * v;
	m[2][2] = m[2][2] * v;
	m[2][3] = m[2][3] * v;
}

void red::Matrix4::toTransformationMatrix(const red::Vector3 &position, red::Quaternion &quat, const float &s) {
	setIdentity();

	red::Quaternion v1;
	quat.normalize(v1);
	v1.createMatrix4(*this);

	translate(position);
	scale(s);

}





void red::Matrix4::toTransformationMatrix(const red::Vector3 &position, red::Quaternion &quat, const red::Vector3 &s) {
	setIdentity();
	rotate(quat);
	translate(position);
	scale(s);

}

void red::Matrix4::setIdentity() {
	clearMatrix();
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
}

void red::Matrix4::clearMatrix() {
	for (int i = 0; i < 4; i++) {
		m[i][0] = 0;
		m[i][1] = 0;
		m[i][2] = 0;
		m[i][3] = 0;
	}
}

void red::Matrix4::setValues(float**v) {
	for(int i = 0; i < 4; i++) {
		m[i][0] = v[i][0];
		m[i][1] = v[i][1];
		m[i][2] = v[i][2];
		m[i][3] = v[i][3];
	}
}

red::Vector4 red::Matrix4::operator *(const Vector4 &v) const {
	return red::Vector4(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w, m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w, m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w, m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w);
}

red::Matrix4 red::Matrix4::operator *(const Matrix4 &v) const {
	float **mm = new float*[4];
	mm[0] = new float[4];
	mm[1] = new float[4];
	mm[2] = new float[4];
	mm[3] = new float[4];

	mm[0][0] = m[0][0] * v.m[0][0] + m[0][1] * v.m[1][0] + m[0][2] * v.m[2][0] + m[0][3] * v.m[3][0];
	mm[0][1] = m[0][0] * v.m[0][1] + m[0][1] * v.m[1][1] + m[0][2] * v.m[2][1] + m[0][3] * v.m[3][1];
	mm[0][2] = m[0][0] * v.m[0][2] + m[0][1] * v.m[1][2] + m[0][2] * v.m[2][2] + m[0][3] * v.m[3][2];
	mm[0][3] = m[0][0] * v.m[0][3] + m[0][1] * v.m[1][3] + m[0][2] * v.m[2][3] + m[0][3] * v.m[3][3];

	mm[1][0] = m[1][0] * v.m[0][0] + m[1][1] * v.m[1][0] + m[1][2] * v.m[2][0] + m[1][3] * v.m[3][0];
	mm[1][1] = m[1][0] * v.m[0][1] + m[1][1] * v.m[1][1] + m[1][2] * v.m[2][1] + m[1][3] * v.m[3][1];
	mm[1][2] = m[1][0] * v.m[0][2] + m[1][1] * v.m[1][2] + m[1][2] * v.m[2][2] + m[1][3] * v.m[3][2];
	mm[1][3] = m[1][0] * v.m[0][3] + m[1][1] * v.m[1][3] + m[1][2] * v.m[2][3] + m[1][3] * v.m[3][3];

	mm[2][0] = m[2][0] * v.m[0][0] + m[2][1] * v.m[1][0] + m[2][2] * v.m[2][0] + m[3][3] * v.m[3][0];
	mm[2][1] = m[2][0] * v.m[0][1] + m[2][1] * v.m[1][1] + m[2][2] * v.m[2][1] + m[3][3] * v.m[3][1];
	mm[2][2] = m[2][0] * v.m[0][2] + m[2][1] * v.m[1][2] + m[2][2] * v.m[2][2] + m[3][3] * v.m[3][2];
	mm[2][3] = m[2][0] * v.m[0][3] + m[2][1] * v.m[1][3] + m[2][2] * v.m[2][3] + m[3][3] * v.m[3][3];

	mm[3][0] = m[3][0] * v.m[0][0] + m[3][1] * v.m[1][0] + m[3][2] * v.m[2][0] + m[3][3] * v.m[3][0];
	mm[3][1] = m[3][0] * v.m[0][1] + m[3][1] * v.m[1][1] + m[3][2] * v.m[2][1] + m[3][3] * v.m[3][1];
	mm[3][2] = m[3][0] * v.m[0][2] + m[3][1] * v.m[1][2] + m[3][2] * v.m[2][2] + m[3][3] * v.m[3][2];
	mm[3][3] = m[3][0] * v.m[0][3] + m[3][1] * v.m[1][3] + m[3][2] * v.m[2][3] + m[3][3] * v.m[3][3];

	return red::Matrix4(mm);
}

red::Matrix4 red::multiplyTwoMatricies(const red::Matrix4 &m1, const red::Matrix4 &m2) {
	return red::Matrix4(m1 * m2);
}


void red::Matrix4::rotate(const red::Quaternion &v) {
	red::Matrix4 quat;

	red::Quaternion v1;
	v.normalize(v1);
	v1.createMatrix4(quat);

	Matrix4 mat(multiplyTwoMatricies(quat, *this));
	setValues(mat.m);
}

void red::Matrix4::toProjectionMatrix(float width, float height, float FOV, float zFar, float zNear) {
	clearMatrix();
	m[0][0] = (height / width) * (1 / tan(FOV / 2));
	m[1][1] = (1 / tan(FOV / 2));
	m[2][2] = zFar / (zFar - zNear);
	m[2][3] = 1;
	m[3][2] = (-zFar * zNear) / (zFar - zNear);
}

// QUATERNION ##########################################################################

red::Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {

}
red::Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

}

red::Quaternion::Quaternion(const red::Vector3 &axis, float rot) : x(0), y(0), z(0), w(1) {
	fromAxis(axis, rot);
}

void red::Quaternion::fromAxis(const red::Vector3 &axis, float angle) {
	angle *= 0.5f;
	Vector3 vn(axis.x, axis.y, axis.z);
	vn.normalize();

	float sinAngle = sin(angle);

	x = (vn.x * sinAngle);
	y = (vn.y * sinAngle);
	z = (vn.z * sinAngle);
	w = cos(angle);
}

void red::Quaternion::createMatrix4(Matrix4 &matrix) const {
	matrix.m[0][0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
	matrix.m[0][1] = 2.0f * x * y - 2.0f * z * w;
	matrix.m[0][2] = 2.0f * x * z + 2.0f * y * w;
	matrix.m[0][3] = 0.0f;

	matrix.m[1][0] = 2.0f * x * y + 2.0f * z * w;
	matrix.m[1][1] = 1.0f - 2.0f * x * x - 2.0f * z * z;
	matrix.m[1][2] = 2.0f * y * z - 2.0f * x * w;
	matrix.m[1][3] = 0.0f;

	matrix.m[2][0] = 2.0f * x * z - 2.0f * y * w;
	matrix.m[2][1] = 2.0f * y * z + 2.0f * x * w;
	matrix.m[2][2] = 1.0f - 2.0f * x * x - 2.0f * y * y;
	matrix.m[2][3] = 0.0f;

	matrix.m[3][0] = 0.0f;
	matrix.m[3][1] = 0.0f;
	matrix.m[3][2] = 0.0f;
	matrix.m[3][3] = 1.0f;

}

void red::Quaternion::normalize(Quaternion &v) const {
	float d = sqrt(x * x + y * y + z * z + w * w);
	v.x = x / d;
	v.y = y / d;
	v.z = z / d;
	v.w = w / d;
}

void red::Quaternion::createMatrix3(red::Matrix3 &matrix) {

	matrix.m[0][0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
	matrix.m[0][1] = 2.0f * x * y - 2.0f * z * w;
	matrix.m[0][2] = 2.0f * x * z + 2.0f * y * w;

	matrix.m[1][0] = 2.0f * x * y + 2.0f * z * w;
	matrix.m[1][1] = 1.0f - 2.0f * x * x - 2.0f * z * z;
	matrix.m[1][2] = 2.0f * y * z - 2.0f * x * w;

	matrix.m[2][0] = 2.0f * x * z - 2.0f * y * w;
	matrix.m[2][1] = 2.0f * y * z + 2.0f * x * w;
	matrix.m[2][2] = 1.0f - 2.0f * x * x - 2.0f * y * y;

}

red::Quaternion red::Quaternion::operator*(const red::Quaternion &v) {
	return Quaternion(x * v.w + w * v.x + y * v.z - z * v.y,
			y * v.w + w * v.y + z * v.x - x * v.z,
			z * v.w + w * v.z + x * v.y - y * v.x,
			w * v.w - x * v.x - y * v.y - z * v.z);
}

