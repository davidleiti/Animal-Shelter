#pragma once
#include "Repository.h"
class CSVRepo : public Repository {
private:
	void loadFromFile(std::istream& in) override;
	void writeToFile(std::ostream& out) override;
	std::string fileName;
public:
	CSVRepo(const std::string& fileName);
	~CSVRepo() override;
};