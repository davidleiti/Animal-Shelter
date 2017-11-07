#include "guinterface.hpp"
#include <vector>
#include <string>

using namespace std;

GUInterface::GUInterface(Controller& controller, QWidget * parent) :QWidget{ parent } , cont(controller) {
	this->cont = controller;
	this->adoptionList = new HTMLAdoptionList{"al.html"};
	this->initializeWidget();
	this->connectSignals();
	emit listModifiedSignal();
}

GUInterface::~GUInterface() {}

void GUInterface::initializeWidget()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };
	
	QWidget* admin = new QWidget{};
	QVBoxLayout* adminLayout = new QVBoxLayout{admin};
	QWidget* middleButtons = new QWidget{};
	QHBoxLayout * buttonLayout = new QHBoxLayout{ middleButtons };
	QWidget* user = new QWidget{};
	QVBoxLayout* userLayout = new QVBoxLayout{ user };
	
	mainLayout->addWidget(admin);
	mainLayout->addWidget(user);
	
	this->comboBoxWidget = new QComboBox{};
	this->comboBoxWidget->addItem(QString::fromStdString("Detailed"));
	this->comboBoxWidget->addItem(QString::fromStdString("Short"));
	adminLayout->addWidget(this->comboBoxWidget);

	this->repoListWidget = new QListWidget{};
	adminLayout->addWidget(this->repoListWidget);

	QWidget* middle = new QWidget{};
	QFormLayout* fields = new QFormLayout{ middle };
	this->nameWidget = new QLineEdit{};
	this->breedWidget = new QLineEdit{};
	this->ageWidget = new QLineEdit{};
	this->linkWidget = new QLineEdit{};
	this->filterWidget = new QLineEdit{};
	fields->addRow( " &Name: ", this->nameWidget );
	fields->addRow( " &Breed: ", this->breedWidget );
	fields->addRow( " &Age: ", this->ageWidget );
	fields->addRow(" &Link: ", this->linkWidget );
	fields->addRow(" &Filter: ", this->filterWidget);

	QWidget* bottom = new QWidget{};
	QHBoxLayout* buttons = new QHBoxLayout{bottom};
	this->addButton = new QPushButton{ " &Add " };
	this->removeButton = new QPushButton{ " &Remove " };
	this->updateButton = new QPushButton{ " & Update " };
	buttons->addWidget(this->addButton);
	buttons->addWidget(this->removeButton);
	buttons->addWidget(this->updateButton);
	
	adminLayout->addWidget(middle);
	adminLayout->addWidget(bottom);
	adminLayout->addWidget(middleButtons);

	this->adoptButton = new QPushButton{ " &Adopt " };
	buttonLayout->addWidget(adoptButton);
	this->openLinkButton = new QPushButton{ " &Open photo " };
	buttonLayout->addWidget(openLinkButton);

	this->adoptionListWidget = new QListWidget{};
	userLayout->addWidget(adoptionListWidget);

	this->adoptionListOverviewWidget = new QPushButton{ " &View adoption list " };
	userLayout->addWidget(adoptionListOverviewWidget);
}

void GUInterface::populateList()
{
	if (this->repoListWidget->count() != 0)
		this->repoListWidget->clear();
	string field = this->filterWidget->text().QString::toStdString();
	vector<Dog> list = this->cont.filteredVector(field, 0);
	if (this->comboBoxWidget->currentText() == QString::fromStdString("Detailed"))
		for (Dog d : list) {
			string s = d.getName() + " - " + d.getBreed() + " - " + to_string(d.getAge());
			QFont font{ "Verdana",10 };
			QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
			item->setFont(font);
			this->repoListWidget->addItem(item);
		}
	else for (Dog d : list) {
		QFont font{ "Verdana",10 };
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(d.getName()) };
		item->setFont(font);
		this->repoListWidget->addItem(item);
	}
	if (this->repoListWidget->count() != 0)
		this->repoListWidget->setCurrentRow(0);
}

void GUInterface::populateAdoptionList() {
	if (this->adoptionListWidget->count() != 0)
		this->adoptionListWidget->clear();	
	vector<Dog> list = this->adoptionList->getVector();
	for (Dog d : list) {
		string s = d.getName() + " - " + d.getBreed() + " - " + to_string(d.getAge());
		QFont font{ "Verdana",10 };
		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
		item->setFont(font);
		this->adoptionListWidget->addItem(item);
	}
	if (this->adoptionListWidget->count() != 0)
		this->adoptionListWidget->setCurrentRow(0);
}

void GUInterface::connectSignals()
{
	QObject::connect(this->addButton, SIGNAL(clicked()), this, SLOT(addButtonHandler()));
	QObject::connect(this, &GUInterface::listModifiedSignal, this, &GUInterface::populateList);
	QObject::connect(this->removeButton, SIGNAL(clicked()), this, SLOT(removeButtonHandler()));
	QObject::connect(this->repoListWidget, &QListWidget::itemSelectionChanged, this, &GUInterface::listSelectionChanged);
	QObject::connect(this->openLinkButton, SIGNAL(clicked()), this, SLOT(openPhotoHandler()));
	QObject::connect(this->adoptButton, SIGNAL(clicked()), this, SLOT(adoptButtonHandler()));
	QObject::connect(this, &GUInterface::adoptionListModifiedSignal, this, &GUInterface::populateAdoptionList);
	QObject::connect(this->adoptionListOverviewWidget, SIGNAL(clicked()), this, SLOT(adoptionListShowButtonHandler()));
	QObject::connect(this->updateButton, SIGNAL(clicked()), this, SLOT(updateButtonHandler()));
	QObject::connect(this->comboBoxWidget, &QComboBox::currentTextChanged, this, &GUInterface::populateList);
	QObject::connect(this->filterWidget, &QLineEdit::textChanged, this, &GUInterface::populateList);
}

void GUInterface::addButtonHandler()
{
	string name = this->nameWidget->text().toStdString();
	string breed = this->breedWidget->text().toStdString();
	int age = this->ageWidget->text().toInt();
	string link = this->linkWidget->text().toStdString();
	try {
		this->cont.addDog(name, breed, age, link);
		emit listModifiedSignal();
	}
	catch (RepositoryException& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
}


void GUInterface::removeButtonHandler()
{
	string name = this->nameWidget->text().toStdString();
	try {
		this->cont.removeDog(name);
		emit listModifiedSignal();
	}
	catch (RepositoryException& re) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", re.what());
	}
}

void GUInterface::updateButtonHandler() {
	string name = this->nameWidget->text().toStdString();
	string newBreed = this->breedWidget->text().toStdString();
	int newAge = this->ageWidget->text().toInt();
	string newLink = this->linkWidget->text().toStdString();
	try{
		this->cont.updateDog(name, newBreed, newAge, newLink);
		emit listModifiedSignal();
	}
	catch (RepositoryException& re) {
		QMessageBox errorBox;
		errorBox.critical(0, "Error", re.what());
	}
}

void GUInterface::openPhotoHandler() {
	int pos = this->getSelectionIndex();
	try {
		Dog d = this->cont.getElementOnPos(pos);
		d.openPhoto();
	}
	catch (RepositoryException& re) {
		QMessageBox errorBox;
		errorBox.critical(0, "Error", "Nothing to do here..");
	}
}

void GUInterface::adoptButtonHandler() {
	int pos = this->getSelectionIndex();
	try {
		Dog d = this->cont.getElementOnPos(pos);
		this->adoptionList->adopt(d);
		this->adoptionList->store();
		this->cont.removeDog(d.getName());
		emit adoptionListModifiedSignal();
		emit listModifiedSignal();
	}
	catch (RepositoryException& re) {
		QMessageBox errorBox;
		errorBox.critical(0, "Error", "Nothing to do here...");
	}
}

void GUInterface::adoptionListShowButtonHandler() {
	this->adoptionList->overView();
}

int GUInterface::getSelectionIndex() {
	if (this->repoListWidget->count() == 0)
		return -1;
	QModelIndexList index = this->repoListWidget->selectionModel()->selectedIndexes();
	if (index.size() == 0) {
		this->nameWidget->clear();
		this->breedWidget->clear();
		this->ageWidget->clear();
		this->linkWidget->clear();
		return -1;
	}
	return index.at(0).row();
}

void GUInterface::listSelectionChanged() {
	int index = this->getSelectionIndex();
	if (index == -1 || index > this->cont.getVectorLength())
		return;
	Dog d = this->cont.getElementOnPos(index);
	this->nameWidget->setText(QString::fromStdString(d.getName()));
	this->breedWidget->setText(QString::fromStdString(d.getBreed()));
	this->ageWidget->setText(QString::number(d.getAge()));
	this->linkWidget->setText(QString::fromStdString(d.getPhoto()));
}
