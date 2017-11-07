#include "Dog.h"
#include <Windows.h>
#include <shellapi.h>

using namespace std;

int Dog::instanceNr = 0;

Dog::Dog(const std::string&  name, const std::string& breed, int age, const std::string& photo)
{
	this->name = name;
	this->age = age;
	this->breed = breed;
	this->photo = photo;
	instanceNr++;
}

Dog & Dog::operator=(const Dog & d)
{
	this->name = d.getName();
	this->breed = d.getBreed();
	this->age = d.getAge();
	this->photo = d.photo;
	return *this;
}

Dog::Dog(const Dog & d)
{
	this->name = d.name;
	this->breed = d.breed;
	this->age = d.age;
	this->photo = d.photo;
	instanceNr++;
}

void Dog::openPhoto()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->photo.c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::string Dog::DogToString()
{
	std::string age = std::to_string(this->age);
	return "Name: " + this->name + "\nBreed: " + this->breed + "\nAge: " + age + "\n";
}

vector<std::string> tokenize(const std::string & line, char delimiter)
{
	vector<string> res;
	stringstream s(line);
	string aux;
	while (getline(s, aux, delimiter))
		res.push_back(aux);
	return res;
}



std::ostream & operator<<(std::ostream & os, const Dog & d)
{
	os << d.name << ',' << d.breed << ',' << to_string(d.age) << ',' << d.photo << '\n';
	return os;
}

std::istream & operator>>(std::istream& is, Dog& d) {
	string line;
	getline(is, line);
	vector<string> fields = tokenize(line, ',');
	if (fields.size() != 4) return is;
	d.name = fields[0];
	d.breed = fields[1];
	d.age = std::stoi(fields[2]);
	d.photo = fields[3];
	return is;
}


