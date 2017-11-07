#include "HTMLAdoptionList.h"
#include <fstream> 
#include <Windows.h>
#include <iostream>
#include <shellapi.h>
using namespace std;

HTMLAdoptionList::HTMLAdoptionList()
{

}

void HTMLAdoptionList::store()
{
	ofstream os{ this->fileName };
	os << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>Adoption List</title>\n\t</head>\n\t<body>\n";
	os << "\t\t<table border=" << "\"1\"" << ">\n\t\t <tr>\n\t\t\t<td>Name</td>\n";
	os << "\t\t\t<td>Breed</td>\n\t\t\t<td>Age</td>\n\t\t\t<td>Photo link</td>\n\t\t</tr>\n";
	for (Dog d : this->list) {
		os << "\t\t<tr>\n\t\t\t<td>" << d.getName() << "</td>\n\t\t\t<td>" << d.getBreed() << "</td>\n";
		os << "\t\t\t<td>" << std::to_string(d.getAge()) << "</td>\n\t\t\t<td><a href=\"" << d.getPhoto();
		os << "\">Link</a></td>\n\t\t</tr>\n";
	}
	os << "\t</body>\n</html>";
	os.close();
}

void HTMLAdoptionList::adopt(Dog & d)
{
	this->list.push_back(d);
}

void HTMLAdoptionList::overView()
{
	if (fileName != "")
		ShellExecuteA(NULL, NULL, "chrome.exe", this->fileName.c_str(), NULL, SW_SHOWNORMAL);

}

