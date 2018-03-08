#include <glew.h>
#include "MyGlWindow.h"
#include <math\vector3D.h>
#include <Debug Tools\Profiling\profiler.h>
#include <Debug Tools\Profiling\Profile.h>
#include <Time\Clock.h>
#include <QtGui\QKeyEvent>
#include <cassert>
#include <iostream>
#include <Math\matrix2DH.h>

using Math::vector3D;
using Timing::Clock;
using Math::matrix2DH;

MyGlWindow::MyGlWindow()
{
}


MyGlWindow::~MyGlWindow()
{
}

namespace {

	vector3D shipVerts[] =
	{
		vector3D(+0.0f, +0.14142135623f,1.0f),
		vector3D(-0.1f, -0.1f,1.0f),
		vector3D(+0.1f, -0.1f,1.0f)

		/*vector3D(+0.0f, +0.14142135623f*0,1.0f*0),
		vector3D(-0.1f*0, -0.1f,1.0f*0),
		vector3D(+0.1f*0, -0.1f,1.0f*0)*/
	};

	vector3D boundaryVerts[]
	{
		vector3D(+0.0f, +1.0f, +0.0f),
		vector3D(-1.0f, +0.0f, +0.0f),
		vector3D(+0.0f, -1.0f, +0.0f),
		vector3D(+1.0f, +0.0f, +0.0f)

		/*vector3D(+0.0f, +0.0f, +0.0f),
		vector3D(-0.0f, +0.0f, +0.0f),
		vector3D(+0.0f, -0.0f, +0.0f),
		vector3D(+1.0f, +0.0f, +0.0f)*/
	};
	vector3D lerpPoints[] =
	{
		vector3D(+0.5f,+0.5f,+0.0f),
		vector3D(-0.5f,+0.5f,+0.0f),
		vector3D(-0.5f,-0.5f,+0.0f),
		vector3D(+0.5f,-0.5f,+0.0f)
	};
	uint sourceLerpPoint;
	uint destinationLerpPoint;
	const uint NUM_LERP_POINTS = sizeof(lerpPoints) / sizeof(*lerpPoints);
	float alpha;
	vector3D currentLerperPosition;
	GLushort indices[] = { 0,1,1,2,2,3,3,0 };
	static const unsigned int NUM_SHIP_VERTS = sizeof(shipVerts) / sizeof(*shipVerts);
	static const unsigned int NUM_BOUNDARY_VERTS = sizeof(boundaryVerts) / sizeof(*boundaryVerts);
	GLuint shipVertexBufferID;
	GLuint boundaryVertsBufferID;
	GLuint boundaryIndexBufferID;
	vector3D shipPosition(-0.0f, -0.0f,0.0f);
	vector3D transformedVerts[NUM_SHIP_VERTS];
	vector3D shipVelocity(0.0f, 0.0f);
	vector3D oldShipPosition;
	float shipDirection = 0.0f;
	Clock clock;
	
}

bool MyGlWindow::shutdown()
{
	profiler.shutdown();
	return clock.shutdown();
}

bool MyGlWindow::initialize()
{
	bool ret = true;
	profiler.initialize("profilesTime.csv");
	ret &= clock.initialize();
	if (NUM_LERP_POINTS > 1)
	{
		alpha = 0.0f;
		/*sourceLerpPoint = 0;
		destinationLerpPoint = sourceLerpPoint + 1;*/
		destinationLerpPoint = 0;
		targetNextLerpPoint();
	}
	else
		ret = false;
	return ret;
}

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);
	
	glGenBuffers(1, &shipVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipVerts), NULL, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &boundaryVertsBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertsBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundaryVerts), boundaryVerts, GL_STATIC_DRAW);

	glGenBuffers(1,&boundaryIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boundaryIndexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);
}

void MyGlWindow::update()
{
	clock.lap();
	profiler.newFrame();
	rotateShip();
	updateVelocity();
	oldShipPosition = shipPosition;
	shipPosition += shipVelocity * clock.lastLapTime();
	handleBoundaries();
	lerpTheLerper();
}

void MyGlWindow::doGL()
{
	//Setup viewport
	glViewport(0.0f, 0.0f, width(), height());
	//Setup data pointers
	//glClear(GL_COLOR_BUFFER_BIT);
	
	glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	
	//glBindBuffer(GL_ARRAY_BUFFER, shipVertexBufferID);
	//Send data to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, boundaryVertsBufferID);
	glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, 0, 0);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(boundaryVerts), boundaryVerts);
	//Draw
	glDrawElements(GL_LINES, 8,GL_UNSIGNED_SHORT,0);
}

void MyGlWindow::handleBoundaries()
{
	const int EDGE_POSITION = 1;
	//Bouncing
	/*if (shipPosition.x < -EDGE_POSITION || shipPosition.x > EDGE_POSITION)
		shipVelocity.x *= -1;
	if (shipPosition.y < -EDGE_POSITION || shipPosition.y > EDGE_POSITION)
		shipVelocity.y *= -1;*/
	
	//Wrapping
	/*if (shipPosition.y > EDGE_POSITION)
		shipPosition.y = -1;
	if (shipPosition.y < -EDGE_POSITION)
		shipPosition.y = 1;
	if (shipPosition.x > EDGE_POSITION)
		shipPosition.x = -1;
	if (shipPosition.x < -EDGE_POSITION)
		shipPosition.x = 1;*/

	//diamond
	for (uint i = 0; i < NUM_BOUNDARY_VERTS; i++)
	{
		const vector3D& first = boundaryVerts[i];
		const vector3D& second = boundaryVerts[(i + 1)% NUM_BOUNDARY_VERTS];

		vector3D wall = second - first;
		vector3D normal = wall.perpCcwXY();
		vector3D respectiveShipPosition = shipPosition - first;
		float dotResult = normal.dot(respectiveShipPosition);

		if (dotResult < 0)
		{
			//shipVelocity = shipVelocity - 2 * shipVelocity.dot(normal)*normal;
			shipVelocity = shipVelocity - 2 * shipVelocity.projectOnto(normal);
			shipPosition = oldShipPosition;
		}
	}

}

void MyGlWindow::lerpTheLerper()
{
	alpha += clock.lastLapTime();
	if (alpha >= 1.0f)
	{
		alpha = 0;
		targetNextLerpPoint();
	}
	const vector3D& source = lerpPoints[sourceLerpPoint];
	const vector3D& destination = lerpPoints[destinationLerpPoint];
	currentLerperPosition = lerp(alpha, source, destination);


}

void MyGlWindow::targetNextLerpPoint()
{
	sourceLerpPoint = destinationLerpPoint;
	destinationLerpPoint = (destinationLerpPoint + 1) % NUM_LERP_POINTS;
}



void MyGlWindow::draw()
{
	matrix2DH translator = matrix2DH::translate(shipPosition.x, shipPosition.y);
	matrix2DH rotator = matrix2DH::rotateZ(shipDirection);
	float aspectRatio = static_cast<float>(width() / height());
	matrix2DH scale;

	if(aspectRatio>1)
		scale = matrix2DH::scale(1.0f / aspectRatio, 1.0f);
	else
		scale = matrix2DH::scale(1.0f,aspectRatio);

	matrix2DH op;
	{
		PROFILE("Matrix Multiplication");
		op = translator * scale * rotator;
	}

	{
		PROFILE("Vector Transformation");
		for (unsigned int i = 0; i < NUM_SHIP_VERTS; i++)
		{
			transformedVerts[i] = op * shipVerts[i];
		}
	}
	glClear(GL_COLOR_BUFFER_BIT);
	doGL();
	translator = matrix2DH::translate(currentLerperPosition.x, currentLerperPosition.y);
	op = translator* scale * rotator;;
	for (unsigned int i = 0; i < NUM_SHIP_VERTS; i++)
	{
		transformedVerts[i] = op * shipVerts[i];
	}

	doGL();

	
}

void MyGlWindow::paintGL()
{
	//update
	update();

	//Paint
	draw();
	
}

void MyGlWindow::keyPressEvent(QKeyEvent * e)
{

}

void MyGlWindow::updateVelocity()
{
	const float ACCELERATION = 0.3f *clock.lastLapTime();
	vector3D dirToAccelerate(-sin(shipDirection), cos(shipDirection));

	if (GetAsyncKeyState(VK_UP) )
		shipVelocity += dirToAccelerate * ACCELERATION;
	if (GetAsyncKeyState(VK_DOWN))
		shipVelocity -= dirToAccelerate * ACCELERATION;
}

void MyGlWindow::rotateShip()
{
	const float ANGULAR_MOVEMENT = 0.1f;
	if (GetAsyncKeyState(VK_LEFT))
		shipDirection += ANGULAR_MOVEMENT;
	if (GetAsyncKeyState(VK_RIGHT))
		shipDirection -= ANGULAR_MOVEMENT;
}

void MyGlWindow::myUpdate()
{
		repaint();
}