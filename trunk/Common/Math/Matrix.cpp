#include "Matrix.h"

CMatrix::CMatrix()
{
	setMatrix(0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0);
}

CMatrix::CMatrix(float m11, float m12, float m13, float m14, 
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
{
	setMatrix(m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44);
}

CMatrix::~CMatrix()
{}

void CMatrix::setMatrix(float m11, float m12, float m13, float m14, 
					float m21, float m22, float m23, float m24,
					float m31, float m32, float m33, float m34,
					float m41, float m42, float m43, float m44)
{
	this->m11 = m11; this->m12 = m12; this->m13 = m13; this->m14 = m14;
	this->m21 = m21; this->m22 = m22; this->m23 = m23; this->m24 = m24;
	this->m31 = m31; this->m32 = m32; this->m33 = m33; this->m34 = m34;
	this->m41 = m41; this->m42 = m42; this->m43 = m43; this->m44 = m44;
}

void CMatrix::loadIdentity()
{
	setMatrix(1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1);
}

CMatrix CMatrix::getInvers()
{
	// TODO 
	return CMatrix();
}

CMatrix CMatrix::getTransposed()
{
	return CMatrix(m11, m21, m31, m41,
		m12, m22, m32, m42,
		m13, m23, m33, m43,
		m14, m24, m34, m44);
}

void CMatrix::operator = (CMatrix& matrix)
{
	setMatrix(matrix.m11, matrix.m12, matrix.m13, matrix.m14,
		matrix.m21, matrix.m22, matrix.m23, matrix.m24,
		matrix.m31, matrix.m32, matrix.m33, matrix.m34,
		matrix.m41, matrix.m42, matrix.m43, matrix.m44);
}

CMatrix CMatrix::operator + (CMatrix& matrix)
{
	return CMatrix(m11 + matrix.m11, m12 + matrix.m12, m13 + matrix.m13, m14 + matrix.m14,
		m21 + matrix.m21, m22 + matrix.m22, m23 + matrix.m23, m24 + matrix.m24,
		m31 + matrix.m31, m32 + matrix.m32, m33 + matrix.m33, m34 + matrix.m34,
		m41 + matrix.m41, m42 + matrix.m42, m43 + matrix.m43, m44 + matrix.m44);
}

CMatrix CMatrix::operator - (CMatrix& matrix)
{
	return CMatrix(m11 - matrix.m11, m12 - matrix.m12, m13 - matrix.m13, m14 - matrix.m14,
		m21 - matrix.m21, m22 - matrix.m22, m23 - matrix.m23, m24 - matrix.m24,
		m31 - matrix.m31, m32 - matrix.m32, m33 - matrix.m33, m34 - matrix.m34,
		m41 - matrix.m41, m42 - matrix.m42, m43 - matrix.m43, m44 - matrix.m44);
}

CMatrix CMatrix::operator * (CMatrix& matrix)
{
	return CMatrix(m11 * matrix.m11 + m12 * matrix.m21 + m13 * matrix.m31 + m14 * matrix.m41,
		m11 * matrix.m12 + m12 * matrix.m22 + m13 * matrix.m32 + m14 * matrix.m42,
		m11 * matrix.m13 + m12 * matrix.m23 + m13 * matrix.m33 + m14 * matrix.m43,
		m11 * matrix.m14 + m12 * matrix.m24 + m13 * matrix.m34 + m14 * matrix.m44,

		m21 * matrix.m11 + m22 * matrix.m21 + m23 * matrix.m31 + m24 * matrix.m41,
		m21 * matrix.m12 + m22 * matrix.m22 + m23 * matrix.m32 + m24 * matrix.m42,
		m21 * matrix.m13 + m22 * matrix.m23 + m23 * matrix.m33 + m24 * matrix.m43,
		m21 * matrix.m14 + m22 * matrix.m24 + m23 * matrix.m34 + m24 * matrix.m44,

		m31 * matrix.m11 + m32 * matrix.m21 + m33 * matrix.m31 + m34 * matrix.m41,
		m31 * matrix.m12 + m32 * matrix.m22 + m33 * matrix.m32 + m34 * matrix.m42,
		m31 * matrix.m13 + m32 * matrix.m23 + m33 * matrix.m33 + m34 * matrix.m43,
		m31 * matrix.m14 + m32 * matrix.m24 + m33 * matrix.m34 + m34 * matrix.m44,

		m41 * matrix.m11 + m42 * matrix.m21 + m43 * matrix.m31 + m44 * matrix.m41,
		m41 * matrix.m12 + m42 * matrix.m22 + m43 * matrix.m32 + m44 * matrix.m42,
		m41 * matrix.m13 + m42 * matrix.m23 + m43 * matrix.m33 + m44 * matrix.m43,
		m41 * matrix.m14 + m42 * matrix.m24 + m43 * matrix.m34 + m44 * matrix.m44);
}

CMatrix operator + (CMatrix& matrix, float skalar)
{
	return CMatrix(matrix.m11 + skalar, matrix.m12 + skalar, matrix.m13 + skalar, matrix.m14 + skalar,
		matrix.m21 + skalar, matrix.m22 + skalar, matrix.m23 + skalar, matrix.m24 + skalar,
		matrix.m31 + skalar, matrix.m32 + skalar, matrix.m33 + skalar, matrix.m34 + skalar,
		matrix.m41 + skalar, matrix.m42 + skalar, matrix.m43 + skalar, matrix.m44 + skalar);
}

CMatrix operator + (float skalar, CMatrix& matrix)
{
	return matrix + skalar;
}
//CMatrix operator + (CMatrix& matrix, unsigned long skalar);
//CMatrix operator + (unsigned long skalar, CMatrix& matrix);

CMatrix operator - (CMatrix& matrix, float skalar)
{
	return CMatrix(matrix.m11 - skalar, matrix.m12 - skalar, matrix.m13 - skalar, matrix.m14 - skalar,
		matrix.m21 - skalar, matrix.m22 - skalar, matrix.m23 - skalar, matrix.m24 - skalar,
		matrix.m31 - skalar, matrix.m32 - skalar, matrix.m33 - skalar, matrix.m34 - skalar,
		matrix.m41 - skalar, matrix.m42 - skalar, matrix.m43 - skalar, matrix.m44 - skalar);
}
CMatrix operator - (float skalar, CMatrix& matrix)
{
	return matrix - skalar;
}
//CMatrix operator - (CMatrix& matrix, unsigned long skalar);
//CMatrix operator - (unsigned long skalar, CMatrix& matrix);

CMatrix operator * (CMatrix& matrix, float skalar)
{
	return CMatrix(matrix.m11 * skalar, matrix.m12 * skalar, matrix.m13 * skalar, matrix.m14 * skalar,
		matrix.m21 * skalar, matrix.m22 * skalar, matrix.m23 * skalar, matrix.m24 * skalar,
		matrix.m31 * skalar, matrix.m32 * skalar, matrix.m33 * skalar, matrix.m34 * skalar,
		matrix.m41 * skalar, matrix.m42 * skalar, matrix.m43 * skalar, matrix.m44 * skalar);
}
CMatrix operator * (float skalar, CMatrix& matrix)
{
	return matrix * skalar;
}
//CMatrix operator * (CMatrix& matrix, unsigned long skalar);
//CMatrix operator * (unsigned long skalar, CMatrix& matrix);

CMatrix operator / (CMatrix& matrix, float skalar)
{
	return CMatrix(matrix.m11 / skalar, matrix.m12 / skalar, matrix.m13 / skalar, matrix.m14 / skalar,
		matrix.m21 / skalar, matrix.m22 / skalar, matrix.m23 / skalar, matrix.m24 / skalar,
		matrix.m31 / skalar, matrix.m32 / skalar, matrix.m33 / skalar, matrix.m34 / skalar,
		matrix.m41 / skalar, matrix.m42 / skalar, matrix.m43 / skalar, matrix.m44 / skalar);
}
CMatrix operator / (float skalar, CMatrix& matrix)
{
	return matrix / skalar;
}
//CMatrix operator / (CMatrix& matrix, unsigned long skalar);
//CMatrix operator / (unsigned long skalar, CMatrix& matrix);