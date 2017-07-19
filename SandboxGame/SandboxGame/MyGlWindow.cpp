#include <glew.h>
#include <cassert>
#include "MyGlWindow.h"
#include <iostream>

MyGlWindow::MyGlWindow()
{
}


MyGlWindow::~MyGlWindow()
{
}

static float verts[] =
{
	+0.0f, +0.1f,
	-0.1f, -0.1f,
	+0.1f, -0.1f
};

void MyGlWindow::initializeGL()
{
	GLenum errorCode = glewInit();
	assert(errorCode == 0);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	

	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	connect(&myTimer, SIGNAL(timeout()), this, SLOT(myUpdate()));
	myTimer.start(0);

}

void MyGlWindow::paintGL()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MyGlWindow::myUpdate()
{
	std::cout << "frame" << std::endl;
}


