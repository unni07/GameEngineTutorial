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
<<<<<<< HEAD
=======
	bool shutdown();
	bool initialize();
	
>>>>>>> parent of 8a53185... Finally completed the tutorial
	
protected:
	void initializeGL();
	void paintGL();
private slots:
	void myUpdate();
<<<<<<< HEAD
=======
	void updateVelocity();
	void rotateShip();
>>>>>>> parent of 8a53185... Finally completed the tutorial
};

