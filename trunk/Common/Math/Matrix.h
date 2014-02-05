#pragma once

class CMatrix
{
public:
	CMatrix();
	CMatrix(float m11, float m12, float m13, float m14, 
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44);
	virtual ~CMatrix();

// Methode zum beeinflussen der gesamten Matrix
public:
	void setMatrix(	float m11, float m12, float m13, float m14, 
					float m21, float m22, float m23, float m24,
					float m31, float m32, float m33, float m34,
					float m41, float m42, float m43, float m44);
	void loadIdentity();
	
	CMatrix getInvers();
	CMatrix getTransposed();

// Operatoren zum Rechnen
public:
	void operator = (CMatrix& matrix);

	CMatrix operator + (CMatrix& matrix);
	CMatrix operator - (CMatrix& matrix);
	CMatrix operator * (CMatrix& matrix);

public:
	float m11;
	float m12;
	float m13;
	float m14;
	float m21;
	float m22;
	float m23;
	float m24;
	float m31;
	float m32;
	float m33; 
	float m34;
	float m41;
	float m42;
	float m43;
	float m44;
};

CMatrix operator + (CMatrix& matrix, float skalar);
CMatrix operator + (float skalar, CMatrix& matrix);
//CMatrix operator + (CMatrix& matrix, unsigned long skalar);
//CMatrix operator + (unsigned long skalar, CMatrix& matrix);

CMatrix operator - (CMatrix& matrix, float skalar);
CMatrix operator - (float skalar, CMatrix& matrix);
//CMatrix operator - (CMatrix& matrix, unsigned long skalar);
//CMatrix operator - (unsigned long skalar, CMatrix& matrix);

CMatrix operator * (CMatrix& matrix, float skalar);
CMatrix operator * (float skalar, CMatrix& matrix);
//CMatrix operator * (CMatrix& matrix, unsigned long skalar);
//CMatrix operator * (unsigned long skalar, CMatrix& matrix);

CMatrix operator / (CMatrix& matrix, float skalar);
CMatrix operator / (float skalar, CMatrix& matrix);
//CMatrix operator / (CMatrix& matrix, unsigned long skalar);
//CMatrix operator / (unsigned long skalar, CMatrix& matrix);