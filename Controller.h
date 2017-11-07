#pragma once
#include "CSVRepo.h"
class Controller {
private:
	Repository* repo;
public:

	/*Constructor for our controller, taking as parameter an already existing repository object*/
	Controller(Repository* repo) { this->repo = repo; };
	~Controller() { delete this->repo; };
	/*Returns the Dog object found on the given position in the vector used by the repository
	Returns NULL if there is no element on that position*/
	Dog getElementOnPos(int pos) { return this->repo->getElementOnPos(pos); };

	/*Attempts to add a Dog object to the vector our repository
	Returns: true, if the object can be added, or false otherwise(there already is an object with the same name)*/
	void addDog(std::string name, std::string breed, int age, std::string photo);

	/*Attempts to remove a Dog object from the vector our repository
	Returns: true, if the object can be removed
	false(there is no object with the given name in the vector)*/
	void removeDog(std::string name);

	/*Attempts to update a Dog object in the vector our repository
	Returns: true, if the object can be modified
	false(there is no object with the given name in the vector)
	Pre-condition: the given object has the same name as the one we wish to update*/
	void updateDog(std::string name, std::string breed, int age, std::string photo);

	/*Returns the length of the vector of our repository*/
	int getVectorLength() { return this->getRepo()->getVectorLength(); };

	/*Returns the repository of our controller, such that we can access the deeper layers of our application*/
	Repository* getRepo() { return this->repo; };

	/*Returns a DynamicVector object containing the objects satisfying the criterias given as parameters
	(All dogs of a given breed with ages greater than a given value)
	Returns all of the objects from our repository with age greater than the given value, if no breed is given*/
	std::vector<Dog> filteredVector(const std::string breed, int age);
	void clearRepo() { this->repo->clearRepo(); };
};