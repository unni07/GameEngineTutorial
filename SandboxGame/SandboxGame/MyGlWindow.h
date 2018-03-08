#pragma once

#include <QtOpenGL\QGLWidget>
#include <Qt\qtimer.h>

class QKeyEvent;

class MyGlWindow : public QGLWidget
{
	Q_OBJECT


	QTimer myTimer;
	void updateVelocity();
	void rotateShip();
public:
	
	MyGlWindow();
	~MyGlWindow();
	bool shutdown();
	bool initialize();
	void update();
	void draw();
	void doGL();
	void handleBoundaries();
	void lerpTheLerper();
	void targetNextLerpPoint();
protected:
	void initializeGL();
	void paintGL();
	void keyPressEvent(QKeyEvent * e);
private slots:
	void myUpdate();
	
};

