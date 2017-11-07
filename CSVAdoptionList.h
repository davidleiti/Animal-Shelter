#pragma once
#include "AdoptionList.h"
#include <fstream>
class CSVAdoptionList :
	public AdoptionList
{
protected:
	std::string fileName;
public:
	void store() override;
	CSVAdoptionList(const std::string& name) { this->fileName = name; std::ofstream os{ name }; os.close(); };
	~CSVAdoptionList() override { store(); };
	void overView() override;
	void adopt(Dog & d) { this->list.push_back(d); };
};

