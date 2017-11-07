#pragma once
#include "Controller.h"
#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"
#include <iostream>

using namespace std;

class UI {
private:
	Controller cont;
public:
	UI(Controller cont) : cont(cont) {};

	/*First entrypoint of our user interface, asks the user to choose between user and administrator mode*/
	void start();
private:
	/*Reads a string from the user, and returns the read string*/
	std::string readString(const std::string& msg);

	/*Reads an integer from the user, returning the read integer*/
	int readInteger(const std::string& msg);

	/*Main loop of the adminstrator mode of our application*/
	void adminMode();

	/*Main loop of the user mode of our application*/
	void userMode();

	/*Prints the options available in the administrator mode*/
	void printAdminMenu();

	/*Prints the options available in the user mode*/
	void printUserMenu();

	/*Lets the user see all dogs available for adoption, and gives the option of or either
	adopting them, or not*/
	void startAdoption(AdoptionList* adoptionList);

	/*Lets the user see all dogs matching the given filter criterias
	available for adoption, and gives the option of or either adopting them, or not*/
	void startFilteredAdoption(const string& breed, int age, AdoptionList* adoptionList);
};