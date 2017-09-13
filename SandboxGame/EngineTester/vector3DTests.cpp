#include <gtest\gtest.h>
#include <Math\vector3D.h>
using Math::vector3D;

TEST(vector3D, CONSTRUCTOR)
{
	vector3D instance(-4.3f,9.1f,5.0f);
	EXPECT_FLOAT_EQ(instance.x, -4.3f);
	EXPECT_FLOAT_EQ(instance.y, 9.1f);
	EXPECT_FLOAT_EQ(instance.z, 5.0f);

	vector3D defaultConstructor;
	EXPECT_FLOAT_EQ(defaultConstructor.x,0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.y,0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.z,0.0f);
}

TEST(vector3D, ScalarMultiplication)
{
	vector3D instance(1, 2, 3);
	vector3D multiplied1 = 5 * instance;
	vector3D multiplied2 = instance * 5;

	EXPECT_FLOAT_EQ(multiplied1.x, 5.0f);
	EXPECT_FLOAT_EQ(multiplied1.y, 10.0f);
	EXPECT_FLOAT_EQ(multiplied1.z, 15.0f);


	EXPECT_FLOAT_EQ(multiplied2.x, 5.0f);
	EXPECT_FLOAT_EQ(multiplied2.y, 10.0f);
	EXPECT_FLOAT_EQ(multiplied2.z, 15.0f);
}

TEST(vector3D, VectorAddition)
{
	vector3D first(9, -2, 5);
	vector3D second(-4, 5.4, 7);
	vector3D result = first + second;
	EXPECT_FLOAT_EQ(result.x, 5.0f);
	EXPECT_FLOAT_EQ(result.y, 3.4);
	EXPECT_FLOAT_EQ(result.z, 12.0f);
}

TEST(vector3D, assignmentPlus)
{
	vector3D first(9, -2, 5);
	vector3D result;
	result += first;
	EXPECT_FLOAT_EQ(result.x, 9.0f);
	EXPECT_FLOAT_EQ(result.y, -2.0f);
	EXPECT_FLOAT_EQ(result.z, 5.0f);
}