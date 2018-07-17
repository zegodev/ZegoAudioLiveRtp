#include "Dialog/ZegoMainDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

	QApplication app(argc, argv);
	ZegoMainDialog w;
	w.initDialog();
	w.show();
	return app.exec();
}
