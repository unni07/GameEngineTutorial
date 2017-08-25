#include <glew.h>
#include "MyGlWindow.h"
#include <math\vector2D.h>
#include <Time\Clock.h>
#include <QtGui\QKeyEvent>
#include <cassert>
#include <iostream>

using Math::vector2D;
using Timing::Clock;
MyGlWindow::MyGlWindow()
{
}


MyGlWindow::~MyGlWindow()
{
}

namespace {

	vector2D verts[] =
	{
		vector2D(+0.0f, +0.1f),
		vector2D(-0.1f, -0.1f),
		vector2D(+0.1f, -0.1f)
	};
	static const unsigned int NUM_VERTS = sizeof(verts) / sizeof(*verts);
	vector2D shipPosition(-0.0f, -0.0f);
	vector2D translatedVerts[NUM_VERTS];
	vector2D shipVelocity(0.0f, 0.0f);
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

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);
	
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), NULL, GL_DYNAMIC_DRAW);
	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);

}

void MyGlWindow::paintGL()
{

	glViewport(0, 0, width(), height());
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	for (unsigned int i = 0; i < NUM_VERTS; i++)
	{
		translatedVerts[i] = verts[i] + shipPosition;
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(translatedVerts), translatedVerts);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGlWindow::keyPressEvent(QKeyEvent * e)
{

}

void MyGlWindow::updateVelocity()
{
	const float ACCELERATION = 0.3f *clock.timeElapsedLastFrame();
	if (GetAsyncKeyState(VK_UP) )
		shipVelocity.y += ACCELERATION;
	if (GetAsyncKeyState(VK_DOWN))
		shipVelocity.y -= ACCELERATION;
	if (GetAsyncKeyState(VK_LEFT))
		shipVelocity.x -= ACCELERATION;
	if (GetAsyncKeyState(VK_RIGHT))
		shipVelocity.x += ACCELERATION;
}

void MyGlWindow::myUpdate()
{
	clock.newFrame();
	updateVelocity();
	shipPosition += shipVelocity * clock.timeElapsedLastFrame();
	repaint();
}


