#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
class Dog {
private:
	std::string name;
	std::string breed;
	int age;
	std::string photo;

public:
	static int instanceNr;
	/*Basic constructor for the Dog class, which initializes each string field with an empty string, and age with 0*/
	Dog() { this->name = ""; this->breed = ""; this->age = 0; this->photo = "", instanceNr++; };

	/*Copy constructor for the Dog class, copies each field of the given Dog object*/
	Dog(const Dog& d);

	~Dog() { instanceNr--; };

	/*Parameterized constructor, used for instantiating Dog objects by explicitly spcifying it's fields*/
	Dog(const std::string& name, const std::string& breed, int age, const std::string& photo);

	/*Overloads the == operator, returns true of the objects have the same name, false otherwise*/
	bool operator==(const Dog& d) { return this->name == d.getName(); };

	Dog& operator=(const Dog& d);

	/*Returns the name of a Dog object*/
	std::string getName() const { return this->name; };

	/*Returns the breed of a Dog object*/
	std::string getBreed() const { return this->breed; };

	/*Returns the age of a Dog object*/
	int getAge() const { return this->age; };

	std::string getPhoto() const { return this->photo; };

	/*Opens the link to the photo of a Dog object in google chrome using a shell function from the shellapi header*/
	void openPhoto();

	/*Returns a string for representing the Dog object in the console*/
	std::string DogToString();

	friend std::ostream & operator<<(std::ostream& os, const Dog& d);
	friend std::istream & operator>>(std::istream& os, Dog& d);
};