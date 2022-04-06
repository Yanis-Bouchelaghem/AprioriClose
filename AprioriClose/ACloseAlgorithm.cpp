#include "ACloseAlgorithm.h"
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include "Itemset.h"

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
	:
	document(document)
{
	//GenerateTIDs(document);
	GenerateTIDsMultiThreaded(document);
	Go();
	//Itemset itemset({{0,"CO"},{2,"SFO"}},tids,document);
	//itemset.CalculateMetrics();
}

void ACloseAlgorithm::Go()
{
	//Generate 1st itemsets
	itemset = GenerateKItemsets(1);
	//Calculate support for each itemset
	for (auto& item : itemset)
	{
		item.CalculateMetrics();
	}

	//Eliminate itemsets with support < minsup
	
	//Generate 2nd itemsets
	//Calculate support for each itemset
	//Eliminate itemsets with support < minsup
}

void ACloseAlgorithm::GenerateTIDs(const rapidcsv::Document& document)
{
	//Allocate the necessarry memory to hold the TIDs
	tids.resize(document.GetColumnCount());
	//Go through the document and generate the TIDs.
	for (size_t iColumn = 0; iColumn < document.GetColumnCount(); iColumn++)
	{
		//Generate the column values for this column and fill its part in the TIDs.
		auto column = document.GetColumn<std::string>(iColumn);
		for (size_t iRow = 0; iRow < column.size(); ++iRow)
		{
			//Fill the TID of this cell
			tids[iColumn][column[iRow]].emplace_back(iRow);
		}
	}
}

void ACloseAlgorithm::GenerateTIDsMultiThreaded(const rapidcsv::Document& document)
{
	//Allocate the necessarry memory to hold the TIDs
	tids.resize(document.GetColumnCount());
	//Create a worker thread for each column
	std::vector<std::thread> workers;
	//Go through the document and generate the columns values and the TIDs.
	for (size_t iColumn = 0; iColumn < document.GetColumnCount(); ++iColumn)
	{
		const auto worker = [this](const rapidcsv::Document& document,const size_t iColumn) {
			this->GenerateColumnTID(document,iColumn);
		};
		workers.push_back(std::thread{worker, std::ref(document), iColumn});
	}
	//Wait for all workers to finish
	for (auto& worker : workers)
	{
		worker.join();
	}
}

void ACloseAlgorithm::GenerateColumnTID(const rapidcsv::Document& document ,const size_t iColumn)
{
	//Generate the column values for this column and fill its part in the TIDs.
	auto column = document.GetColumn<std::string>(iColumn);
	for (size_t iRow = 0; iRow < column.size(); ++iRow)
	{
		//Fill the TID of this cell
		tids[iColumn][column[iRow]].emplace_back(iRow);
	}
}

std::vector<Itemset> ACloseAlgorithm::GenerateKItemsets(size_t k)
{
	std::vector<Itemset> generatedItemsets;
	//Generate k items
	if (k == 1)
	{
		//Generate 1st itemsets
		for (size_t i = 0; i < tids.size(); ++i)
		{
			for (const auto& tid : tids[i])
			{
				generatedItemsets.emplace_back(std::vector{ std::pair{i,tid.first} }, tids, document);
			}
		}
	}
	return generatedItemsets;
}




