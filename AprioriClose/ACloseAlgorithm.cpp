#include "ACloseAlgorithm.h"
#include <string>
#include <vector>
#include <algorithm>
#include <thread>

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
{
	//GenerateTIDs(document);
	GenerateTIDsMultiThreaded(document);
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




