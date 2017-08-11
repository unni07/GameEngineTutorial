#pragma once

#include <QtOpenGL\QGLWidget>
#include <Qt\qtimer.h>

class MyGlWindow : public QGLWidget
{
	Q_OBJECT

	GLuint vertexBufferID;
	QTimer myTimer;
public:
	
	MyGlWindow();
	~MyGlWindow();
	bool shutdown();
	bool initialize();
	
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
};

