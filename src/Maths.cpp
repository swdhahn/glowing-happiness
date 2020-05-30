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

void red::Vector3::normalize(Vector3 &v) {
	int d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= d;
	v.y /= d;
	v.z /= d;
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
