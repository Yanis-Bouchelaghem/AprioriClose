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
	*/
	void GenerateAllColumnsValues();
	int GetID(const std::string& value);
	std::vector<std::vector<int>> GenerateTIDs();
	void GenerateTIds2();
	
private:
	
	std::vector<std::string> columnsValues; //Stores the possible values each column in the document can have.
	std::vector<int> columnsValuesLastIndex;//Stores the index of the last possible value of each column in the columnsValues vector.

	const rapidcsv::Document& document;
};