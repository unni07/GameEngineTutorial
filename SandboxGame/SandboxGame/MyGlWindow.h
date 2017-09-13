#pragma once

#include <QtOpenGL\QGLWidget>
#include <Qt\qtimer.h>

class QKeyEvent;

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
	void keyPressEvent(QKeyEvent * e);
private slots:
	void myUpdate();
	void updateVelocity();
	void rotateShip();
};

