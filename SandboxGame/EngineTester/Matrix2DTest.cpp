//#include <Math\vector2D.h>
#include <gtest\gtest.h>
#include <Math\matrix2D.h>
#include "HelperFunction.h"
#include <Math\Constants.h>
using Math::matrix2D;
using Math::vector2D;
using Math::M_PI;

//const float PI = 22.0f / 7.0f;
const float PI = 3.14159265358979323846f;
const float sqrt2Over2 = 0.7071067f;
const float sqrt3Over2 = 0.8660254f;

TEST(Matrix2D, Construction)
{
	matrix2D identity;
	EXPECT_FLOAT_EQ(identity.r0c0, 1.0f);
	EXPECT_FLOAT_EQ(identity.r0c1, 0.0f);
	EXPECT_FLOAT_EQ(identity.r1c0, 0.0f);
	EXPECT_FLOAT_EQ(identity.r1c1, 1.0f);
}

TEST(Matrix2D, MatrixVectorMultiply)
{
	matrix2D op(2,-3,
			    4,-5);
	vector2D victim(3, 9);
	vector2D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, -21.0f);
	EXPECT_FLOAT_EQ(victimPrime.y, -33.0f);
}

TEST(Matrix2D, Rotation)
{
	matrix2D op = matrix2D::rotate(0.0f);
	EXPECT_FLOAT_EQ(op.r0c0, 1.0f);
	EXPECT_FLOAT_EQ(op.r0c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c1, 1.0f);

	op = matrix2D::rotate(M_PI);
	EXPECT_TRUE(closeEnough(op.r0c0, -1.0f));
	EXPECT_TRUE(closeEnough(op.r0c1, 0.0f));
	EXPECT_TRUE(closeEnough(op.r1c0, 0.0f));
	EXPECT_TRUE(closeEnough(op.r1c1, -1.0f));

	op = matrix2D::rotate(PI/2);
	EXPECT_TRUE(closeEnough(op.r0c0, 0.0f));
	EXPECT_FLOAT_EQ(op.r0c1, -1.0f);
	EXPECT_FLOAT_EQ(op.r1c0, 1.0f);
	EXPECT_TRUE(closeEnough(op.r1c1, 0.0f));

	op = matrix2D::rotate(PI/4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);

	op = matrix2D::rotate(-PI/4);
	EXPECT_FLOAT_EQ(op.r0c0, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt2Over2);
	EXPECT_FLOAT_EQ(op.r1c1, sqrt2Over2);

	op = matrix2D::rotate(PI / 3);
	EXPECT_FLOAT_EQ(op.r0c0, 0.5f);
	EXPECT_FLOAT_EQ(op.r0c1, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c0, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, 0.5f);

	op = matrix2D::rotate(-PI / 3);
	EXPECT_FLOAT_EQ(op.r0c0, 0.5f);
	EXPECT_FLOAT_EQ(op.r0c1, sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c0, -sqrt3Over2);
	EXPECT_FLOAT_EQ(op.r1c1, 0.5f);
}

