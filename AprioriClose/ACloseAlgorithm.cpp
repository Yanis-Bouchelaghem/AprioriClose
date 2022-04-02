#include "ACloseAlgorithm.h"
#include <string>
#include <vector>
#include <algorithm>

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
{
	GenerateTIDs(document);
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

int ACloseAlgorithm::FindColumnValueID(const std::string& value, int column)
{
	const auto result = std::find(valuesIndex[column].begin(), valuesIndex[column].end(), value);
	if (result != valuesIndex[column].end())
	{
		//Find the ID of the value by adding the length of the previous columns.
		int idOffset = 0;
		for (int i = 0; i < column; ++i)
		{
			idOffset += int(valuesIndex[i].size());
		}
		return int((result - valuesIndex[column].begin()) + idOffset);
	}
	else
		return -1;
}




