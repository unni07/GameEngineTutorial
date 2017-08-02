#include <glew.h>
#include <cassert>
#include "MyGlWindow.h"
#include <iostream>
#include <math\vector2D.h>
using Math::vector2D;

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
	vector2D shipPosition(0.5f, 0.5f);
	vector2D translatedVerts[NUM_VERTS];
	vector2D velocity(0.001f, 0.001f);
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

void MyGlWindow::myUpdate()
{
	shipPosition = shipPosition + velocity;
	repaint();
}


