#include <glew.h>
<<<<<<< HEAD
=======
#include "MyGlWindow.h"
#include <math\vector3D.h>
#include <Time\Clock.h>
#include <QtGui\QKeyEvent>
>>>>>>> parent of 8a53185... Finally completed the tutorial
#include <cassert>
#include "MyGlWindow.h"
#include <iostream>
<<<<<<< HEAD
=======
#include <Math\matrix3D.h>

using Math::vector3D;
using Timing::Clock;
using Math::matrix3D;
>>>>>>> parent of 8a53185... Finally completed the tutorial

MyGlWindow::MyGlWindow()
{
}


MyGlWindow::~MyGlWindow()
{
}

<<<<<<< HEAD
static float verts[] =
{
	+0.0f, +0.1f,
	-0.1f, -0.1f,
	+0.1f, -0.1f
};
=======
namespace {

	vector3D verts[] =
	{
		vector3D(+0.0f, +0.14142135623f,1.0f),
		vector3D(-0.1f, -0.1f,1.0f),
		vector3D(+0.1f, -0.1f,1.0f)
	};
	static const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	vector3D shipPosition(-0.0f, -0.0f,0.0f);
	vector3D transformedVerts[NUM_VERTS];
	vector3D shipVelocity(0.0f, 0.0f);
	float shipDirection = 0.0f;
	Clock clock;
	
}

bool MyGlWindow::shutdown()
{
	return clock.shutdown();
}

bool MyGlWindow::initialize()
{
	return clock.initialize();
	initializeGL();
	return true;
}
>>>>>>> parent of 8a53185... Finally completed the tutorial

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);
<<<<<<< HEAD

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);

=======
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), NULL, GL_DYNAMIC_DRAW);
	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);
>>>>>>> parent of 8a53185... Finally completed the tutorial
}

void MyGlWindow::paintGL()
{
<<<<<<< HEAD
=======
	int minSize = min(width(), height());
	vector3D viewPortLocation;
	//viewPortLocation.x = width();// / 2.0f - minSize / 2.0f;
	//viewPortLocation.y = height();// / 2.0f, minSize / 2.0f;
	viewPortLocation.x = width() / 2.0f - minSize / 2.0f;
	viewPortLocation.y = height()/ 2.0f - minSize / 2.0f;
	glViewport(viewPortLocation.x, viewPortLocation.y,minSize, minSize);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	matrix3D translator = matrix3D::translate(shipPosition.x, shipPosition.y);
	matrix3D rotator = matrix3D::rotateZ(shipDirection);
	matrix3D op = translator * rotator;
	for (unsigned int i = 0; i < NUM_VERTS; i++)
	{
		transformedVerts[i] = op * verts[i];
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(transformedVerts), transformedVerts);
	glDrawArrays(GL_TRIANGLES, 0, 9);
}

void MyGlWindow::keyPressEvent(QKeyEvent * e)
{
>>>>>>> parent of 8a53185... Finally completed the tutorial

	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGlWindow::myUpdate()
{
<<<<<<< HEAD
	std::cout << "frame" << std::endl;
=======
	const float ACCELERATION = 0.3f *clock.timeElapsedLastFrame();
	vector3D dirToAccelerate(-sin(shipDirection), cos(shipDirection));

	if (GetAsyncKeyState(VK_UP) )
		shipVelocity += dirToAccelerate * ACCELERATION;
	if (GetAsyncKeyState(VK_DOWN))
		shipVelocity -= dirToAccelerate * ACCELERATION;
>>>>>>> parent of 8a53185... Finally completed the tutorial
}


<<<<<<< HEAD
=======
void MyGlWindow::myUpdate()
{
	clock.newFrame();
	rotateShip();
	updateVelocity();
	shipPosition += shipVelocity * clock.timeElapsedLastFrame();
	repaint();
}
>>>>>>> parent of 8a53185... Finally completed the tutorial
