#include "UI.h"
#include <sstream>
#include <fstream>
using namespace std;

void UI::start()
{
	cout << "\t1. <- Administrator mode" << endl << "\t2. <- User mode" << endl << "\t0. <- Exit" << endl;
	bool ok = false;
	while (!ok) {
		int mode = readInteger("Choose a mode: ");
		if (mode == 1) adminMode();
		else if (mode == 2) userMode();
		else if (mode == 0) {
			ok = true;
			cout << "The program will now exit...Bye!" << endl;
		}
		else cout << "The input must be 1 or 2, please try again!" << endl;
	}
}

void UI::adminMode()
{
	printAdminMenu();
	bool ok = false;
	while (!ok) {
		try {
			int input = readInteger("Enter a command: ");
			switch (input) {
			case 1:
			{
				string name = readString("Enter the name of the dog: ");
				string breed = readString("Enter the breed: ");
				int age = readInteger("Enter the age: ");
				string photo = readString("Enter the link to a photo: ");
				this->cont.addDog(name, breed, age, photo);
				cout << "Dog added successfully!" << endl;
				break;
			}
			case 2:
			{
				string name = readString("Enter the name of the dog: ");
				this->cont.removeDog(name);
				cout << "Dog " << name << " removed successfully!" << endl;
				break;
			}
			case 3:
			{
				string name = readString("Enter the name of the dog: ");
				cout << "Now, please enter the new information " << endl;
				string breed = readString("Breed: ");
				int age = readInteger("Enter the age: ");
				string photo = readString("Link to the photo: ");
				this->cont.updateDog(name, breed, age, photo);
				cout << "Dog updated successfully!" << endl;
				break;
			}
			case 4:
			{
				vector<Dog> vect = this->cont.getRepo()->getVector();
				for (auto iter = vect.begin(); iter < vect.end(); iter++) {
					cout << iter->DogToString() << endl;
				}
				break;
			}
			case 5:
				cout << "There are currently " << Dog::instanceNr << " dogs created" << endl;
			case 0:
			{
				ok = true;
				cout << "Leaving user mode..." << endl;
				cout << "\t1. <- Administrator mode" << endl << "\t2. <- User mode" << endl << "\t0. <- Exit" << endl;
				break;
			}
			default:
				cout << "Oops, invalid command, please try again!" << endl;
				break;
			}
		}
		catch (RepositoryException re) {
			cout << re.what() << endl;
		};
	}
}

void UI::printUserMenu() {
	cout << "\t1. <- Start adopting" << endl;
	cout << "\t2. <- Fancy adoption list" << endl;
	cout << "\t3. <- See adoption list" << endl;
	cout << "\t0. <- Leave user mode" << endl;
}


void UI::userMode() {
	AdoptionList* adoptionList = nullptr;
	bool stop = false;
	cout << "\t1. Save adoption list to a comma-separated text file\n\t2. Save adoption list to HTML file " << endl;
	int mode = readInteger("Enter your choice: ");
	if (mode == 1) adoptionList = new CSVAdoptionList{ "adoptionlist.txt" };
	else if (mode == 2) adoptionList = new HTMLAdoptionList{ "adoptionlist.html" };
	else {
		cout << "No valid choice entered, leaving user mode..." << endl;
		return;
	}
	printUserMenu();
	while (!stop) {
		try {
			int input = readInteger("Enter a command: ");
			switch (input) {
			case 1:
			{
				startAdoption(adoptionList);
				adoptionList->store();
				break;
			}
			case 2:
			{
				string breed = readString("Enter the breed: ");
				int age = readInteger("Enter the age: ");
				startFilteredAdoption(breed, age, adoptionList);
				adoptionList->store();
				break;
			}
			case 3:
			{
				if (adoptionList != nullptr)
					adoptionList->overView();
				break;
			}
			case 0:
				stop = true;
				cout << "Leaving user mode..." << endl;
				cout << "\t1. <- Administrator mode" << endl << "\t2. <- User mode" << endl << "\t0. <- Exit" << endl;
				break;
			}
		}
		catch (RepositoryException re) {
			cout << re.what() << endl;
		}
	}
	delete adoptionList;
}

void UI::printAdminMenu()
{
	cout << "Administrator commands: " << endl;
	cout << "\t1. <- Add a new dog " << endl;
	cout << "\t2. <- Remove a dog  " << endl;
	cout << "\t3. <- Update the information of a given dog " << endl;
	cout << "\t4. <- Show all dogs in the repository" << endl;
	cout << "\t5. <- Show number of dogs created" << endl;
	cout << "\t0. <- Exit " << endl;
}

void UI::startAdoption(AdoptionList* adoptionList)
{
	if (this->cont.getVectorLength() > 0) {
		int current = 0;
		bool stop = false;
		while (!stop) {
			if (current == this->cont.getRepo()->getVector().size() - 1) current = 0;
			Dog actualDog = this->cont.getElementOnPos(current);
			cout << actualDog.DogToString();
			actualDog.openPhoto();
			string response = readString("Do you wish to adopt this guy? Y/N (Press 0 to exit session)\n");
			if (response == "Y" || response == "y") {
				adoptionList->adopt(actualDog);
				this->cont.removeDog(actualDog.getName());
				current--;
			}
			else if (response == "0") {
				stop = true;
				cout << "Leaving adoption session, press 3 to see adopted dogs" << endl;
			}
			current++;
		}
	}
	else cout << "No dogs to adopt!" << endl;
}

void UI::startFilteredAdoption(const string & breed, int age, AdoptionList * adoptionList)
{
	vector<Dog> vect = this->cont.filteredVector(breed, age);
	bool stop = false;
	while (!stop) {
		if (vect.empty()) {
			cout << "There are no (more) dogs satisfying the given entry..." << endl;
			break;
		}
		int current = 0;
		Dog actualDog = vect[current];
		cout << actualDog.DogToString();
		actualDog.openPhoto();
		string response = readString("Do you wish to adopt this guy? Y/N (Press 0 to exit session)\n");
		if (response == "Y" || response == "y") {
			adoptionList->adopt(actualDog);
			this->cont.removeDog(actualDog.getName());
			vect.erase(vect.begin() + current);
			current--;
		}
		else if (response == "0") {
			stop = true;
			cout << "Leaving adoption session, press 3 to see adopted dogs" << endl;
		}
		current++;
	}
}


string UI::readString(const string& msg)
{
	cout << msg;
	string input = "";
	getline(cin, input);
	return input;
}

int UI::readInteger(const string& msg)
{
	int res;
	string input = "";
	bool stop = false;
	while (!stop) {
		try {
			cout << msg;
			getline(cin, input);
			stringstream myStream(input);
			if (myStream >> res) stop = true;
			else throw "Not an integer!";
		}
		catch (const char* errMsg) {
			cout << errMsg << endl;
		}
	}
	return res;
}


