#pragma once

#include <QtOpenGL\QGLWidget>

class MyGlWindow : public QGLWidget
{
public:
	
	MyGlWindow();
	~MyGlWindow();
	GLuint vertexBufferID;
protected:
	void initializeGL();
	void paintGL();
};

