#include <gtest\gtest.h>
#include <Math\matrix3D.h>
#include <Math\matrix2DH.h>
#include <Math\vector3D.h>
#include <Misc\TypeDefs.h>
#include "HelperFunction.h"
#include <Math\Constants.h>
using Math::matrix3D;
using Math::vector3D;
using Math::matrix2DH;
using Math::M_PI;
const float sqrt2Over2 = 0.7071067f;
const float sqrt3Over2 = 0.8660254f;
const float PI = 3.14159265358979323846f;

template<class T>
void evaluateLastRow(const T& op)
{
	if (typeid(T) == typeid(matrix3D)) 
	{
		const JE::uint NUM_ELEMENTS_IN_FIRST_TWO_ROWS = 6;
		const float* p = reinterpret_cast<const float*>(&op);
		p += NUM_ELEMENTS_IN_FIRST_TWO_ROWS;
		EXPECT_FLOAT_EQ(*p++, 0);
		EXPECT_FLOAT_EQ(*p++, 0);
		EXPECT_FLOAT_EQ(*p, 1);
	}
}

TEST(Matrix3D, Construction)
{
	{
		matrix3D victim(
			1, 2, 3,
			4, 5, 6,
			7, 8, 9);
		EXPECT_FLOAT_EQ(victim.r0c0, 1);
		EXPECT_FLOAT_EQ(victim.r0c1, 2);
		EXPECT_FLOAT_EQ(victim.r0c2, 3);
		EXPECT_FLOAT_EQ(victim.r1c0, 4);
		EXPECT_FLOAT_EQ(victim.r1c1, 5);
		EXPECT_FLOAT_EQ(victim.r1c2, 6);
		EXPECT_FLOAT_EQ(victim.r2c0, 7);
		EXPECT_FLOAT_EQ(victim.r2c1, 8);
		EXPECT_FLOAT_EQ(victim.r2c2, 9);

		matrix3D identity;
		EXPECT_FLOAT_EQ(identity.r0c0, 1);
		EXPECT_FLOAT_EQ(identity.r0c1, 0);
		EXPECT_FLOAT_EQ(identity.r0c2, 0);
		EXPECT_FLOAT_EQ(identity.r1c0, 0);
		EXPECT_FLOAT_EQ(identity.r1c1, 1);
		EXPECT_FLOAT_EQ(identity.r1c2, 0);
		EXPECT_FLOAT_EQ(identity.r2c0, 0);
		EXPECT_FLOAT_EQ(identity.r2c1, 0);
		EXPECT_FLOAT_EQ(identity.r2c2, 1);
	}

	{
		matrix2DH victim(
			1, 2, 3,
			4, 5, 6);
		EXPECT_FLOAT_EQ(victim.r0c0, 1);
		EXPECT_FLOAT_EQ(victim.r0c1, 2);
		EXPECT_FLOAT_EQ(victim.r0c2, 3);
		EXPECT_FLOAT_EQ(victim.r1c0, 4);
		EXPECT_FLOAT_EQ(victim.r1c1, 5);
		EXPECT_FLOAT_EQ(victim.r1c2, 6);

		matrix2DH identity;
		EXPECT_FLOAT_EQ(identity.r0c0, 1);
		EXPECT_FLOAT_EQ(identity.r0c1, 0);
		EXPECT_FLOAT_EQ(identity.r0c2, 0);
		EXPECT_FLOAT_EQ(identity.r1c0, 0);
		EXPECT_FLOAT_EQ(identity.r1c1, 1);
		EXPECT_FLOAT_EQ(identity.r1c2, 0);
	}
}

TEST(Matrix3D, MatrixVectorMultiply)
{
	{
		matrix3D op(
			1, 2, 3,
			4, 5, 6,
			7, 8, 9);

		vector3D victim(1, 2, 3);
		vector3D victimPrime = op * victim;
		/*vector3D rhs(1,2,3);
		vector3D temp;
		temp.x = op.r0c0 * rhs.x + op.r0c1 * rhs.y + op.r0c2 + rhs.z;
		temp.y = op.r1c0 * rhs.x + op.r1c1 * rhs.y + op.r1c2 + rhs.z;
		temp.z = op.r2c0 * rhs.x + op.r2c1 * rhs.y + op.r2c2 + rhs.z;*/
		EXPECT_FLOAT_EQ(victimPrime.x, 14);
		EXPECT_FLOAT_EQ(victimPrime.y, 32);
		EXPECT_FLOAT_EQ(victimPrime.z, 50);
	}
	{
		matrix2DH op2(
			1, 2, 3,
			4, 5, 6);

		vector3D victim(1, 2, 3);
		vector3D victimPrime = op2 * victim;
		/*vector3D rhs(1,2,3);
		vector3D temp;
		temp.x = op.r0c0 * rhs.x + op.r0c1 * rhs.y + op.r0c2 + rhs.z;
		temp.y = op.r1c0 * rhs.x + op.r1c1 * rhs.y + op.r1c2 + rhs.z;
		temp.z = op.r2c0 * rhs.x + op.r2c1 * rhs.y + op.r2c2 + rhs.z;*/
		EXPECT_FLOAT_EQ(victimPrime.x, 14);
		EXPECT_FLOAT_EQ(victimPrime.y, 32);
		EXPECT_FLOAT_EQ(victimPrime.z, 3);
	}
}

template<class T>
void testRotation()
{
	T op = T::rotateZ(0.0f);
	EXPECT_FLOAT_EQ(op.r0c0, 1);
	EXPECT_FLOAT_EQ(op.r0c1, 0);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, 0);
	EXPECT_FLOAT_EQ(op.r1c1, 1);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);

	op = T::rotateZ(M_PI);
	EXPECT_TRUE(closeEnough(op.r0c0, -1.0f));
	EXPECT_TRUE(closeEnough(op.r0c1, 0.0f));
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_TRUE(closeEnough(op.r1c0, 0.0f));
	EXPECT_TRUE(closeEnough(op.r1c1, -1.0f));
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);


	op = T::rotateZ(PI / 2);
	EXPECT_TRUE(closeEnough(op.r0c0, 0.0f));
	EXPECT_FLOAT_EQ(op.r0c1, -1.0f);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, 1.0f);
	EXPECT_TRUE(closeEnough(op.r1c1, 0.0f));
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);


	op = T::rotateZ(PI / 4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);


	op = T::rotateZ(-PI / 4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);


	op = T::rotateZ(PI / 3);
	EXPECT_FLOAT_EQ(op.r0c0, 0.5f);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, 0.5f);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);


	op = T::rotateZ(-PI / 3);
	EXPECT_FLOAT_EQ(op.r0c0, 0.5f);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r0c2, 0);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, 0.5f);
	EXPECT_FLOAT_EQ(op.r1c2, 0);
	evaluateLastRow(op);

}

TEST(matrix3D, Rotation)
{
	testRotation<matrix3D>();
	testRotation<matrix2DH>();
}

template<class T>
void testTranslation()
{
	T translator = T::translate(4.0f, 8.0f);
	vector3D victim(-3, 8, 1);
	vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1.0f);
	EXPECT_FLOAT_EQ(victimPrime.y, 16.0f);
	EXPECT_FLOAT_EQ(victimPrime.z, 1.0f);
}

TEST(matrix3D, Translation)
{
	testTranslation<matrix3D>();
	testTranslation<matrix2DH>();
}

template<class T>
void testScale()
{
	vector3D victim(6.0f, 5.0f);
	T op = T::scale(0.5f, 2.0f);
	vector3D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 3.0f);
	EXPECT_FLOAT_EQ(victimPrime.y, 10.0f);
	EXPECT_FLOAT_EQ(victimPrime.z, 0.0f);
}

TEST(Matrix3D, Scale)
{
	testScale<matrix3D>();
	testScale<matrix2DH>();
}

TEST(matrix3D, MatrixMultiplication)
{
	{
		matrix3D victim(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	matrix3D identity = victim * victim;
	EXPECT_FLOAT_EQ(identity.r0c0, 30);
	EXPECT_FLOAT_EQ(identity.r0c1, 36);
	EXPECT_FLOAT_EQ(identity.r0c2, 42);
	EXPECT_FLOAT_EQ(identity.r1c0, 66);
	EXPECT_FLOAT_EQ(identity.r1c1, 81);
	EXPECT_FLOAT_EQ(identity.r1c2, 96);
	EXPECT_FLOAT_EQ(identity.r2c0, 102);
	EXPECT_FLOAT_EQ(identity.r2c1, 126);
	EXPECT_FLOAT_EQ(identity.r2c2, 150);
	}
	{
		matrix3D victim(
			1, 2, 3,
			4, 5, 6);

		matrix3D identity = victim * victim;
		EXPECT_FLOAT_EQ(identity.r0c0, 9);
		EXPECT_FLOAT_EQ(identity.r0c1, 12);
		EXPECT_FLOAT_EQ(identity.r0c2, 18);
		EXPECT_FLOAT_EQ(identity.r1c0, 24);
		EXPECT_FLOAT_EQ(identity.r1c1, 33);
		EXPECT_FLOAT_EQ(identity.r1c2, 48);
	}
}

//TEST(matrix3D, )
//{
//	matrix3D victim(
//		11, 2, 3,
//		4, 51, 6,
//		7, 8, 91);
//	EXPECT_FLOAT_EQ(victim.r0c0, 11);
//	EXPECT_FLOAT_EQ(victim.r0c1, 2);
//	EXPECT_FLOAT_EQ(victim.r0c2, 3);
//	EXPECT_FLOAT_EQ(victim.r1c0, 4);
//	EXPECT_FLOAT_EQ(victim.r1c1, 51);
//	EXPECT_FLOAT_EQ(victim.r1c2, 6);
//	EXPECT_FLOAT_EQ(victim.r2c0, 7);
//	EXPECT_FLOAT_EQ(victim.r2c1, 8);
//	EXPECT_FLOAT_EQ(victim.r2c2, 91);
//
//	matrix3D identity;
//	EXPECT_FLOAT_EQ(identity.r0c0, 1);
//	EXPECT_FLOAT_EQ(identity.r0c1, 0);
//	EXPECT_FLOAT_EQ(identity.r0c2, 0);
//	EXPECT_FLOAT_EQ(identity.r1c0, 0);
//	EXPECT_FLOAT_EQ(identity.r1c1, 1);
//	EXPECT_FLOAT_EQ(identity.r1c2, 0);
//	EXPECT_FLOAT_EQ(identity.r2c0, 0);
//	EXPECT_FLOAT_EQ(identity.r2c1, 0);
//	EXPECT_FLOAT_EQ(identity.r2c2, 1);
//}