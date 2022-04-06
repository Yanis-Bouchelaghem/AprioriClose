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
	/**
	 * @brief (Internally used) Searches if the given value is a possible value in the given column, if it is, its ID is returned,
	 * otherwise -1 is returned.
	 * @param value : The value to search for.
	 * @param column : The column in which to search for the value.
	 * @return The ID of the value if found, otherwise returns -1.
	*/
	int FindColumnValueID(const std::string& value, size_t column);
private:
	std::vector<std::vector<std::string>> valuesIndex; //Holds all possible values each column can have.
	std::vector<std::vector<int>> tids; //Holds the TID representation of the document.
};