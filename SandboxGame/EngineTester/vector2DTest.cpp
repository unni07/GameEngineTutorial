#include <gtest\gtest.h>
#include <Math\vector2D.h>

using Math::vector2D;

//vector2DTest::vector2DTest()
//{
//}
//
//
//vector2DTest::~vector2DTest()
//{
//}

TEST(vector2D, CONSTRUCTOR)
{
	vector2D first(1, 2);
	EXPECT_EQ(1, first.x);
	EXPECT_EQ(2, first.y);
}



TEST(vector2D, VectorAddition)
{
	vector2D first(1, 2);
	vector2D second(3, 4);

	vector2D result1 = first + second;
	vector2D result2 = second + first;

	EXPECT_TRUE(result1.x == 4);
	EXPECT_TRUE(result1.y == 6);

	EXPECT_TRUE(result1.x == result2.x);
	EXPECT_TRUE(result1.y == result2.y);

}

TEST(vector2D, ScalarMultiplication)
{
	vector2D first(1, 2);
	float x = 5.0f;

	vector2D result1 = first * x;
	vector2D result2 = x * first;

	EXPECT_FLOAT_EQ(result1.x , 5.0);
	EXPECT_FLOAT_EQ(result1.y , 10.0);

	EXPECT_FLOAT_EQ(result2.x , 5.0);
	EXPECT_FLOAT_EQ(result2.y , 10.0);
}

TEST(vector2D, CopyConstructor)
{
	vector2D source(5, -1234.56);
	vector2D theCopy(source);
	EXPECT_FLOAT_EQ(theCopy.x, source.x);
	EXPECT_FLOAT_EQ(theCopy.y, source.y);
}

TEST(vector2D, assignmentOperator)
{
	vector2D source(5, -1234.56);
	vector2D theCopy;
	theCopy = source;
	EXPECT_FLOAT_EQ(theCopy.x, source.x);
	EXPECT_FLOAT_EQ(theCopy.y, source.y);
}

TEST(vector2D, AssignmentPlusEquals)
{
	vector2D source(5, -1234);
	vector2D theCopy(5,5);
	theCopy += source;
	EXPECT_FLOAT_EQ(theCopy.x, source.x +5);
	EXPECT_FLOAT_EQ(theCopy.y, source.y + 5);
}