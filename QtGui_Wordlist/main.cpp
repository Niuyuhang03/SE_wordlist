#include "QtGui_Wordlist.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtGui_Wordlist w;
	w.show();
	return a.exec();
}
