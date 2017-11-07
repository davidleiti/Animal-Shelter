#pragma once
#include "Dog.h"
#include <string>
#include <vector> 

class RepositoryException : public std::exception {
public:
	explicit RepositoryException(const char* msg) :errorMsg(msg) {};
	~RepositoryException()  throw() {};
	const char* what() const throw() { return this->errorMsg.c_str(); };
protected:
	std::string errorMsg;
};

class Repository {
protected:
	std::vector<Dog> vect;
public:
	/*Adds a Dog object to the repository, raises RepositoryException if there already is a dog with the given name*/
	void add(const Dog& d);

	/*Removes a Dog object from the repository, specified by its name, raises RepositoryException, if there is no
	dog with the given name stored beforehand*/
	void remove(const std::string& name);

	/*Returns the position of the dog specified by its name, returns -1 if the given dog is not stored yet in the repository*/
	int find(const std::string& name);

	/*Updates the information of a given Dog, making it possible to change its breed, age, or photo link.
	Raises RepositoryException if there is no such dog in the repository*/
	void update(const Dog& d);

	/*Returns the length of the vector object used by the repository*/
	int getVectorLength() { return (int)this->vect.size(); };

	/*Returns the vector used by the repository such that we can access its elements*/
	std::vector<Dog> getVector() { return this->vect; };

	/*Returns the element from the vector used by the repository found at a given position*/
	Dog getElementOnPos(int pos) { if (pos >= this->vect.size()) throw RepositoryException{ "There is no such position in the vector" }; return this->vect[pos]; };

	/*Initializes the vector by adding 7 default Dog objects to the vector, making the application easier to test*/
	void initializeVector();
	void clearRepo() { this->vect.clear(); };
	virtual ~Repository() {};
	virtual void loadFromFile(std::istream& in) {};
	virtual void writeToFile(std::ostream& out) {};
};