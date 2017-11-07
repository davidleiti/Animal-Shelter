#include "repository.h"
#include <vector>
#include <iostream>

void Repository::add(const Dog& d)
{
	if (this->find(d.getName()) != -1) throw RepositoryException{ "A dog with the given name is already registered!" };
	this->vect.push_back(d);

}

void Repository::remove(const std::string & name)
{
	int pos = this->find(name);
	if (pos == -1) throw RepositoryException{ "There is no registered dog with that name!" };
	this->vect.erase(this->vect.begin() + pos);
}

int Repository::find(const std::string & name)
{
	int count = 0;
	for (std::vector<Dog>::iterator i = this->vect.begin(); i < this->vect.end(); i++, count++) {
		if (i->getName() == name) return count;
	}
	return -1;
}

void Repository::update(const Dog& d)
{
	int pos = this->find(d.getName());
	if (pos == -1) throw RepositoryException{ "There is no registered dog with that name!" };
	this->vect[pos] = d;
}

void Repository::initializeVector()
{
	this->vect.clear();
	Dog d4{ "Max","Labrador",5,"http://cdn2-www.dogtime.com/assets/uploads/gallery/labrador-retriever-dog-breed-pictures/labrador-retriever-dog-pictures-6.jpg" };
	Dog d2{ "Rex","Husky",5,"http://kutyafajtak.hu/kepek/sziberiai-husky-kutya/sziberiai-husky-kutya-01.jpg" };
	Dog d3{ "Bones","Beagle",2,"http://www.dogbreedinfo.com/images24/BeagleBayleePurebredDogs8Months1.jpg" };
	Dog d1{ "Doge","Shiba",3,"https://pbs.twimg.com/profile_images/378800000822867536/3f5a00acf72df93528b6bb7cd0a4fd0c.jpeg" };
	Dog d5{ "Klondike","American Eskimo",4,"http://vignette3.wikia.nocookie.net/biches-of-jacksfilms/images/c/c5/Klondike.png/revision/latest?cb=20160723212136" };
	Dog d6{ "Sundae","American Eskimo",2,"https://i.ytimg.com/vi/lnfmId5nsjk/maxresdefault.jpg" };
	Dog d7{ "Edgar Allan Pug","Pug",3,"http://vignette3.wikia.nocookie.net/pewdiepie/images/1/19/Edgar_1.png/revision/latest?cb=20131014082030" };
	this->vect.push_back(d1);
	this->vect.push_back(d2);
	this->vect.push_back(d3);
	this->vect.push_back(d4);
	this->vect.push_back(d5);
	this->vect.push_back(d6);
	this->vect.push_back(d7);
}

