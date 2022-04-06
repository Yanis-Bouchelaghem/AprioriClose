#pragma once
#include <vector>
#include <string>
#include "rapidcsv.h"

class ACloseAlgorithm
{
public:
	/**
	 * @brief Constructor, reads the given document once and generates its TID representation.
	 * @param document : The document to read.
	*/
	ACloseAlgorithm(const rapidcsv::Document& document);

private:
	/**
	 * @brief (Internally used) Indexes all possible values of each column and generates the TIDs in one sweep of the document.
	*/
	void GenerateTIDs(const rapidcsv::Document& document);
	void GenerateTIDsMultiThreaded(const rapidcsv::Document& document);
	void GenerateColumnTID(const rapidcsv::Document& document, const size_t iColumn);
private:
	std::vector<std::map<std::string, std::vector<size_t>>> tids; //Holds the TID representation of the document.
};