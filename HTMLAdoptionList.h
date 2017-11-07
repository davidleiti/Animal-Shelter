#pragma once
#include "AdoptionList.h"
#include <vector>
#include <fstream>
class HTMLAdoptionList :
	public AdoptionList
{
public:
	HTMLAdoptionList();
	HTMLAdoptionList(const std::string& fName) { this->fileName = fName; std::ofstream os{ fName }; os.close(); };
	~HTMLAdoptionList() override { this->store(); };
	void store() override;
	void adopt(Dog& d) override;
	void overView() override;
private:
	std::string fileName;
};

