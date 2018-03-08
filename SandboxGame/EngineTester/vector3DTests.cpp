#include <gtest\gtest.h>
#include <Math\Constants.h>
#include <Math\vector3D.h>
#include <Misc\TypeDefs.h>
using JE::uint;
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

TEST(vector3D, Subtraction)
{
	vector3D first(8,3,9);
	vector3D second(7, 1,5);
	vector3D result = first - second;
	EXPECT_FLOAT_EQ(result.x, 1);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 4);
	result = second- first;
	EXPECT_FLOAT_EQ(result.x, -1);
	EXPECT_FLOAT_EQ(result.y, -2);
	EXPECT_FLOAT_EQ(result.z, -4);
}


TEST(vector3D, Perpendicularity)
{
	vector3D meVector(4, 2);
	vector3D perpCw = meVector.perpCwXY();
	vector3D perpCcw = meVector.perpCcwXY();
	EXPECT_FLOAT_EQ(perpCw.x,2 );
	EXPECT_FLOAT_EQ(perpCw.y, -4);
	EXPECT_FLOAT_EQ(perpCcw.x, -2);
	EXPECT_FLOAT_EQ(perpCcw.y, 4);
}

TEST(vector3D, DotProduct)
{
	vector3D first(1, 2, 3);
	vector3D second(4, 5, 6);
	float result = first.dot(second);
	EXPECT_FLOAT_EQ(result, 32);
}

TEST(vector3D, Magnitude)
{
	vector3D ourVector(3,4,5);
	float magnitude = ourVector.magnitude();
	EXPECT_FLOAT_EQ(magnitude, 7.071067811);
}

TEST(vector3D, MagnitudeSquared)
{
	vector3D outVector(3.0f, 4.0f, 5.0f);
	float magnitudeSquared = outVector.magnitudeSquared();
	EXPECT_FLOAT_EQ(magnitudeSquared, 50.0f);

	vector3D ourVector2(0.0f, 6.0f, 0.0f);
	EXPECT_FLOAT_EQ(ourVector2.magnitudeSquared(), 36.0f);
}

TEST(vector4D, Normalization)
{
	vector3D vec(1, 2, 3);
	vector3D normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, 0.26726124);
	EXPECT_FLOAT_EQ(normalized.y, 0.53452247);
	EXPECT_FLOAT_EQ(normalized.z, 0.80178368);

	vec = vector3D(-2.8, 8.4, -3.14);
	normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, -0.2980417);
	EXPECT_FLOAT_EQ(normalized.y, 0.894125);
	EXPECT_FLOAT_EQ(normalized.z, -0.33423254);
}

void testProjectionAlgorithm(const vector3D& source, const vector3D& target)
{
	vector3D targetNormalized = target.normalized();
	vector3D oldResult = source.dot(targetNormalized)*targetNormalized;
	vector3D newResult = source.projectOnto(target);
	EXPECT_FLOAT_EQ(newResult.x, oldResult.x);
	EXPECT_FLOAT_EQ(newResult.y, oldResult.y);
	EXPECT_FLOAT_EQ(newResult.z, oldResult.z);
}

TEST(vector3D, ProjectOnto)
{
	vector3D source(2, 4);
	vector3D target(1, 0);
	vector3D result = source.projectOnto(target);

	EXPECT_FLOAT_EQ(result.x, 2.0f );
	EXPECT_FLOAT_EQ(result.y, 0.0f);
	EXPECT_FLOAT_EQ(result.z, 0.0f);

	vector3D vectors[] =
	{
		vector3D(1.0f, 2.0f, 3.0f),
		vector3D(4.8f, 9.1f, 5.6f),
		vector3D(0.0f,5.0f ,0.0f),
		vector3D(-3.2f,-4.9f ,6.7f),
		vector3D(2.4f, 3.1f,-99.6f),
	};
	const uint NUM_VECTORS = sizeof(vectors) / sizeof(*vectors);

	for (uint i = 0; i < NUM_VECTORS - 1; i++)
	{
		testProjectionAlgorithm(vectors[i], vectors[i + 1]);
		testProjectionAlgorithm(vectors[i+1], vectors[i ]);	
	}

	vector3D a(0.5f,sqrt(3.0f)/2.0f);
	vector3D b(sqrt(3.00f) / 2.0f, 0.5f);

	float dotResult = a.dot(b);
	EXPECT_FLOAT_EQ(dotResult, cos(Math::M_PI /6.0f));
}

TEST(vector3D, lerp)
{
	vector3D source(4.7f,9.2f,7.1f);
	vector3D target(7.4f,2.9f,1.7f);
	vector3D difference = target - source;
	float alpha = 0.0f;
	while (alpha <= 1.0f)
	{
		vector3D lerpResult1 = lerp(alpha, source, target);
		vector3D lerpResult2 = source + alpha*difference;
		EXPECT_FLOAT_EQ(lerpResult1.x, lerpResult2.x);
		EXPECT_FLOAT_EQ(lerpResult1.y, lerpResult2.y);
		EXPECT_FLOAT_EQ(lerpResult1.z, lerpResult2.z);
		alpha += 0.01f;
	}
}