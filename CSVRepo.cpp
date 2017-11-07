#include "CSVrepo.h"
#include <sstream>
#include <fstream>

using namespace std;

void CSVRepo::loadFromFile(std::istream& in)
{
	Dog aux{};
	while (in >> aux) {
		add(aux);
	}
}

void CSVRepo::writeToFile(std::ostream & out)
{
	for (int i = 0; i < this->vect.size(); i++)
		out << this->vect[i];
}

CSVRepo::CSVRepo(const std::string& fileName)
{
	this->fileName = fileName;
	std::ifstream in(fileName);
	loadFromFile(in);
	in.close();
}

CSVRepo::~CSVRepo()
{
	std::ofstream out(this->fileName);
	writeToFile(out);
	out.close();
}


