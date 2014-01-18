#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

#include "Matrix.h"

namespace Tests
{
	[TestClass]
	public ref class TestMatrix
	{
	private:
		TestContext^ testContextInstance;

	public: 
		
		#pragma region Additional test attributes
		//
		//Sie können beim Schreiben der Tests folgende zusätzliche Attribute verwenden:
		//
		//Mit ClassInitialize führen Sie Code aus, bevor Sie den ersten Test in der Klasse ausführen.
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Mit ClassCleanup führen Sie Code aus, nachdem alle Tests in einer Klasse ausgeführt wurden.
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Mit TestInitialize können Sie vor jedem einzelnen Test Code ausführen.
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Mit TestCleanup können Sie nach jedem Test Code ausführen.
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		#define CHECK_MATRIX_VALUES(matrix, _m11, _m12, _m13, _m14, _m21, _m22, _m23, _m24,_m31, _m32, _m33, _m34, _m41, _m42, _m43, _m44) \
		{ \
			Assert::AreEqual(matrix.m11, (float)_m11); \
			Assert::AreEqual(matrix.m12, (float)_m12); \
			Assert::AreEqual(matrix.m13, (float)_m13); \
			Assert::AreEqual(matrix.m14, (float)_m14); \
			Assert::AreEqual(matrix.m21, (float)_m21); \
			Assert::AreEqual(matrix.m22, (float)_m22); \
			Assert::AreEqual(matrix.m23, (float)_m23); \
			Assert::AreEqual(matrix.m24, (float)_m24); \
			Assert::AreEqual(matrix.m31, (float)_m31); \
			Assert::AreEqual(matrix.m32, (float)_m32); \
			Assert::AreEqual(matrix.m33, (float)_m33); \
			Assert::AreEqual(matrix.m34, (float)_m34); \
			Assert::AreEqual(matrix.m41, (float)_m41); \
			Assert::AreEqual(matrix.m42, (float)_m42); \
			Assert::AreEqual(matrix.m43, (float)_m43); \
			Assert::AreEqual(matrix.m44, (float)_m44); \
		  }
		/*
		void checkMatrixValues(CMatrix& matrix, float _m11, float _m12, float _m13, float _m14, 
			float _m21, float _m22, float _m23, float _m24,
			float _m31, float _m32, float _m33, float _m34,
			float _m41, float _m42, float _m43, float _m44)
		{
			Assert::AreEqual(matrix.m11, _m11);
			Assert::AreEqual(matrix.m12, _m12);
			Assert::AreEqual(matrix.m13, _m13);
			Assert::AreEqual(matrix.m14, _m14);
			Assert::AreEqual(matrix.m21, _m21);
			Assert::AreEqual(matrix.m22, _m22);
			Assert::AreEqual(matrix.m23, _m23);
			Assert::AreEqual(matrix.m24, _m24);
			Assert::AreEqual(matrix.m31, _m31);
			Assert::AreEqual(matrix.m32, _m32);
			Assert::AreEqual(matrix.m33, _m33);
			Assert::AreEqual(matrix.m34, _m34);
			Assert::AreEqual(matrix.m41, _m41);
			Assert::AreEqual(matrix.m42, _m42);
			Assert::AreEqual(matrix.m43, _m43);
			Assert::AreEqual(matrix.m44, _m44);
		}
		*/
		[TestMethod]
		void matrixConstructors()
		{
			CMatrix empty;
			CHECK_MATRIX_VALUES(empty, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

			CMatrix values(
				1,2,3,4,
				5,6,7,8,
				9,10,11,12,
				13,14,15,16);
			CHECK_MATRIX_VALUES(values, 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16);
		};

		[TestMethod]
		void loadIdentity()
		{
			CMatrix identity;
			identity.loadIdentity();

			CHECK_MATRIX_VALUES(identity, 
				1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1);
		};

		[TestMethod]
		void transpose()
		{
			CMatrix normal(
				1,2,3,4,
				5,6,7,8,
				9,10,11,12,
				13,14,15,16);

			CMatrix transpose = normal.getTransposed();

			CHECK_MATRIX_VALUES(transpose, 
				1,5,9,13,
				2,6,10,14,
				3,7,11,15,
				4,8,12,16);
		};

		[TestMethod]
		void matrixPlus()
		{
			CMatrix m1(
				1,2,3,4,
				5,6,7,8,
				9,10,11,12,
				13,14,15,16);
			CMatrix m2(
				16,15,14,13,
				12,11,10,9,
				8,7,6,5,
				4,3,2,1);

			CMatrix sum = m1 + m2;
			CHECK_MATRIX_VALUES(sum, 
				17,17,17,17,
				17,17,17,17,
				17,17,17,17,
				17,17,17,17);
			
			sum = m2 + m1;
			CHECK_MATRIX_VALUES(sum, 
				17,17,17,17,
				17,17,17,17,
				17,17,17,17,
				17,17,17,17);
		};

		[TestMethod]
		void matrixMinus()
		{
			CMatrix m1;
			CMatrix m2;

			m1.setMatrix(
				17,17,17,17,
				17,17,17,17,
				17,17,17,17,
				17,17,17,17);
			m2.setMatrix(
				16,15,14,13,
				12,11,10,9,
				8,7,6,5,
				4,3,2,1);

			CMatrix diff = m1 - m2;
			CHECK_MATRIX_VALUES(diff, 
				1,2,3,4,
				5,6,7,8,
				9,10,11,12,
				13,14,15,16);
			
			diff = m2 - m1;
			CHECK_MATRIX_VALUES(diff, 
				-1,-2,-3,-4,
				-5,-6,-7,-8,
				-9,-10,-11,-12,
				-13,-14,-15,-16);
		};

		[TestMethod]
		void matrixMultiply()
		{
			CMatrix m1(
				1,2,3,4,
				5,6,7,8,
				9,10,11,12,
				13,14,15,16);
			CMatrix m2(
				16,15,14,13,
				12,11,10,9,
				8,7,6,5,
				4,3,2,1);

			CMatrix product = m1 * m2;
			CHECK_MATRIX_VALUES(product, 
				80,70,60,50,
				240,214,188,162,
				400,358,316,274,
				560,502,444,386);
			
			product = m2 * m1;
			CHECK_MATRIX_VALUES(product, 
				386,444,502,560,
				274,316,358,400,
				162,188,214,240,
				50,60,70,80);
		};

	};
}
