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
	//Reserve the necessary space for the TIDs.
	tids.resize(document.GetRowCount());
	for (auto& tid : tids)
	{
		tid.resize(document.GetColumnCount());
	}
	//Reserve part of the necessary space for the values index.
	valuesIndex.resize(document.GetColumnCount());

	//Go through the document and generate the columns values and the TIDs.
	for (int iColumn = 0; iColumn < document.GetColumnCount(); iColumn++)
	{
		//Generate the column values for this column and fill its part in the TIDs.
		auto column = document.GetColumn<std::string>(iColumn);
		for (int iRow = 0; iRow < column.size(); ++iRow)
		{
			//Check if this value is not already indexed
			const int valueID = FindColumnValueID(column[iRow], iColumn);
			if (valueID == -1)
			{
				//Add it to the index.
				valuesIndex[iColumn].emplace_back(column[iRow]);
				//Fill the TID of this cell
				tids[iRow][iColumn] = FindColumnValueID(column[iRow], iColumn);
			}
			else
			{
				//Fill the TID of this cell
				tids[iRow][iColumn] = valueID;
			}
		}
	}
}

void ACloseAlgorithm::GenerateTIDsMultiThreaded(const rapidcsv::Document& document)
{
	//Reserve the necessary space for the TIDs.
	tids.resize(document.GetRowCount());
	for (auto& tid : tids)
	{
		tid.resize(document.GetColumnCount());
	}
	//Reserve part of the necessary space for the values index.
	valuesIndex.resize(document.GetColumnCount());

	//Create a worker thread for each column
	std::vector<std::thread> workers;
	//Go through the document and generate the columns values and the TIDs.
	for (int iColumn = 0; iColumn < document.GetColumnCount(); ++iColumn)
	{
		const auto worker = [this](const rapidcsv::Document& document,const int iColumn) {
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

void ACloseAlgorithm::GenerateColumnTID(const rapidcsv::Document& document ,const int iColumn)
{
	//Generate the column values for this column and fill its part in the TIDs.
	auto column = document.GetColumn<std::string>(iColumn);
	for (int iRow = 0; iRow < column.size(); ++iRow)
	{
		//Check if this value is not already indexed
		const int valueID = FindColumnValueID(column[iRow], iColumn);
		if (valueID == -1)
		{
			//Add it to the index.
			valuesIndex[iColumn].emplace_back(column[iRow]);
			//Fill the TID of this cell
			tids[iRow][iColumn] = FindColumnValueID(column[iRow], iColumn);
		}
		else
		{
			//Fill the TID of this cell
			tids[iRow][iColumn] = valueID;
		}
	}
}

int ACloseAlgorithm::FindColumnValueID(const std::string& value, int column)
{
	const auto result = std::find(valuesIndex[column].begin(), valuesIndex[column].end(), value);
	if (result != valuesIndex[column].end())
	{
		return int((result - valuesIndex[column].begin()));
	}
	else
		return -1;
}




