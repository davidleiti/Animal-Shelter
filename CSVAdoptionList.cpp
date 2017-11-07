#include "CSVAdoptionList.h"
#include "Windows.h"
#include <fstream>

void CSVAdoptionList::store()
{
	std::ofstream os{ this->fileName };
	std::string dogs = " ";
	for (Dog d : this->list)
		os << "Name: " << d.getName() + "\tBreed: " + d.getBreed() + "\t\Age: " + std::to_string(d.getAge()) + "\n";
	os << dogs;
	os.close();
}

void CSVAdoptionList::overView()
{
	/*if (fileName != "")
		ShellExecute(NULL, "open", this->fileName.c_str(), NULL, NULL, SW_SHOWNORMAL);*/
}
