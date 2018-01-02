#include "DataAnalyze.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DataAnalyze w;
	w.setWindowIcon(QIcon(":/DataAnalyze/mainIcon"));
	w.show();
	return a.exec();
}
