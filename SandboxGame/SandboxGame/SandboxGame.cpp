#include <QtGui\qapplication.h>
#include <QtGui\qwidget.h>
#include "MyGlWindow.h"
#include <Windows.h>

int main(int argc, char* argv[])
{


	LARGE_INTEGER clockFrequency;
	QueryPerformanceFrequency(&clockFrequency);
	
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;


	QueryPerformanceCounter(&startTime);


	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	myGlWindow.initialize();
	myGlWindow.show();
	int errorCode = application.exec();
	if (!myGlWindow.shutdown())
		errorCode |= 1;
	return errorCode;
}