#include "mainwindow.h"

#include <QtWidgets/QApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QFile>

int main(int argc, char **argv) {

	QApplication application(argc, argv);
	MainWindow window;

	QString theme = "pepper-dark.css";
	QFile qss(QStandardPaths::locate(QStandardPaths::DataLocation, theme));

	if (qss.open(QFile::ReadOnly)) {
		application.setStyleSheet(qss.readAll());
		qss.close();
	}

	window.showMaximized();
	return application.exec();
}
