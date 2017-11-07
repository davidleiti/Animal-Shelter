#include "animal_shelter_gui.h"
#include "Controller.h"
#include <QtWidgets/QApplication>
#include "guinterface.hpp"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CSVRepo* repo = new CSVRepo{"testfile.txt"};
	Controller cont{repo};
	GUInterface gui{cont};
	gui.show();
	return a.exec();
}
