﻿#ifndef __COCOMATRIX_HPP__
#define __COCOMATRIX_HPP__

#include "Coconut2D.hpp"

class CocoMatrix
{
public:
	float rc11;
	float rc12;
	float rc13;
	float rc14;
	float rc21;
	float rc22;
	float rc23;
	float rc24;
	float rc31;
	float rc32;
	float rc33;
	float rc34;
	float rc41;
	float rc42;
	float rc43;
	float rc44;
	Array<Float32Array*>* __stack;
	Float32Array* __data;
	bool __dirty;
	CocoMatrix(CocoMatrix* M = nullptr);
	~CocoMatrix();
	void identity();
	void ortho(float left, float right, float bottom, float top, float near, float far);
	void transpose();
	float determinant();
	void invert();
	CocoVector* multiplyByVector(CocoVector* v);
	CocoMatrix* multiplyByMatrix(CocoMatrix* v);
	void translate(float tx, float ty);
	void scale(float sx, float sy);
	void rotateZ(float rz);
	void refresh();
	void update(WebGLRenderingContext* gl, WebGLUniformLocation* ul);
	void push();
	void pop();
};

#endif
