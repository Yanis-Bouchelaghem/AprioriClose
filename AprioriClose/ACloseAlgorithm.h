#pragma once
#include <vector>
#include <string>
#include "rapidcsv.h"

class ACloseAlgorithm
{
public:
	ACloseAlgorithm(const rapidcsv::Document& document);

private:
	/**
	 * @brief (Used internally) Finds all of the possible values each column in the document can contain, stores them in columnsValues.
	 * The index of the last value of each column is stored in columnsValuesLastIndex.
	 * @param document : The document to scan.
	*/
	void GenerateAllColumnsValues(const rapidcsv::Document& document);
private:
	
	std::vector<std::string> columnsValues; //Stores the possible values each column in the document can have.
	std::vector<int> columnsValuesLastIndex;//Stores the index of the last possible value of each column in the columnsValues vector.
};