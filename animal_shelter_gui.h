#ifndef ANIMAL_SHELTER_GUI_H
#define ANIMAL_SHELTER_GUI_H

#include <QtWidgets/QMainWindow>
#include "ui_animal_shelter_gui.h"

class Animal_Shelter_GUI : public QMainWindow
{
	Q_OBJECT

public:
	Animal_Shelter_GUI(QWidget *parent = 0);
	~Animal_Shelter_GUI();

private:
	Ui::Animal_Shelter_GUIClass ui;
};

#endif // ANIMAL_SHELTER_GUI_H
