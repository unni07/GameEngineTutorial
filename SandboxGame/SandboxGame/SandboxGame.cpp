#include <QtGui\qapplication.h>
#include <QtGui\qwidget.h>
#include "MyGlWindow.h"
<<<<<<< HEAD
=======
#include <Windows.h>
>>>>>>> parent of 8a53185... Finally completed the tutorial

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
<<<<<<< HEAD
	myGlWindow.show();
	return application.exec();
=======
	myGlWindow.initialize();
	myGlWindow.show();
	int errorCode = application.exec();
	if (!myGlWindow.shutdown())
		errorCode |= 1;
	return errorCode;
>>>>>>> parent of 8a53185... Finally completed the tutorial
}