#include <QtWidgets\qapplication.h>
#include <QtWidgets\qwidget.h>
#include "MyGlWindow.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);
	MyGlWindow myGlWindow;
	myGlWindow.show();
	return application.exec();
}