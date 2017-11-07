#pragma once
#include <QVBoxLayout>
#include <QWidget>
#include <QObject>
#include <QListWidget>
#include <qlabel.h>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <qcombobox.h>
#include "Controller.h"
#include "Dog.h"
#include "HTMLAdoptionList.h"
class GUInterface : public QWidget {
	Q_OBJECT

public:
	GUInterface(Controller& controller, QWidget * parent = Q_NULLPTR);
	~GUInterface();
	
private:
	Controller& cont;
	AdoptionList* adoptionList;
	void initializeWidget();
	void populateList();
	void populateAdoptionList();
	void connectSignals();
	int getSelectionIndex();
	void listSelectionChanged();
	QComboBox* comboBoxWidget;
	QListWidget* repoListWidget;
	QListWidget* adoptionListWidget;
	QLineEdit* nameWidget;
	QLineEdit* breedWidget;
	QLineEdit* ageWidget;
	QLineEdit* linkWidget;
	QLineEdit* filterWidget;
	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;
	QPushButton* adoptButton;
	QPushButton* adoptionListOverviewWidget;
	QPushButton* openLinkButton;
signals:
	void listModifiedSignal();
	void adoptionListModifiedSignal();
public slots:
	void addButtonHandler();
	void removeButtonHandler();
	void updateButtonHandler();
	void openPhotoHandler();
	void adoptButtonHandler();
	void adoptionListShowButtonHandler();
};
