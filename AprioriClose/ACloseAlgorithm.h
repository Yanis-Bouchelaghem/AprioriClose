#pragma once
#include <vector>
#include <string>
#include "rapidcsv.h"
#include "Itemset.h"
class ACloseAlgorithm
{
public:
	/**
	 * @brief Constructor, reads the given document once and generates its TID representation.
	 * @param document : The document to read.
	*/
	ACloseAlgorithm(const rapidcsv::Document& document);
	void Go();
private:
	/**
	 * @brief (Internally used) Indexes all possible values of each column and generates the TIDs in one sweep of the document.
	*/
	void GenerateTIDs(const rapidcsv::Document& document);
	void GenerateTIDsMultiThreaded(const rapidcsv::Document& document);
	void GenerateColumnTID(const rapidcsv::Document& document, const size_t iColumn);
	std::vector<Itemset> GenerateKItemsets(size_t k);
private:
	std::vector<std::map<std::string, std::vector<size_t>>> tids; //Holds the TID representation of the document.
	std::vector<std::vector<Itemset>> kItemsets;//Holds the Kth itemsets
	const rapidcsv::Document& document;

	size_t k; //The size of the itemsets to generate
};