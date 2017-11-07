#include "controller.h"
#include <algorithm>

void Controller::addDog(std::string name, std::string breed, int age, std::string photo)
{
	this->repo->add(Dog{ name,breed,age,photo });
}

void Controller::removeDog(std::string name)
{
	this->repo->remove(name);
}

void Controller::updateDog(std::string name, std::string breed, int age, std::string photo)
{
	Dog newDog{ name,breed,age,photo };
	this->repo->update(newDog);
}

std::vector<Dog> Controller::filteredVector(const std::string breed, int age) {
	std::vector<Dog> newVect(this->repo->getVectorLength());
	std::vector<Dog> oldVect = this->repo->getVector();
	int count = 0;
	if (breed == "") {
		auto it = std::copy_if(oldVect.begin(), oldVect.end(), newVect.begin(), [age](Dog i) {return i.getAge() >= age; });
		newVect.resize(std::distance(newVect.begin(), it));
	}
	else {
		auto it = std::copy_if(oldVect.begin(), oldVect.end(), newVect.begin(), [breed, age](Dog i) {return i.getBreed() == breed && i.getAge() >= age; });
		newVect.resize(std::distance(newVect.begin(), it));
	}
	return newVect;
}


