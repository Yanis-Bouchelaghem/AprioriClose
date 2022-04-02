#include "ACloseAlgorithm.h"
#include <string>
#include <vector>
#include <algorithm>

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
	:
	document(document)
{
	GenerateAllColumnsValues();
	auto temp = GenerateTIDs();
	
}

void ACloseAlgorithm::GenerateAllColumnsValues()
{
	for (int i = 0; i < document.GetColumnCount(); ++i)
	{
		//Get a column and find its unique values
		const auto column = document.GetColumn<std::string>(i);
		for (const auto& value : column)
		{
			//Check if the item already exists in the list of items, otherwise, add it 
			//(using an offset to skip searching items that belong to another column)
			int offset = columnsValuesLastIndex.empty() ? 0 : (columnsValuesLastIndex[i - 1] + 1);
			if (std::find(columnsValues.begin() + offset, columnsValues.end(), value) == columnsValues.end())
			{
				columnsValues.emplace_back(value);
			}
		}
		//Save the last ID index of this column
		columnsValuesLastIndex.push_back(columnsValues.size() - 1);
	}
}

int ACloseAlgorithm::GetID(const std::string& value)
{
	//TODO : MAKE IT TAKE A COLUMN INDEX TO SKIP ALL OF THE OTHERS
	auto result = std::find(columnsValues.begin(), columnsValues.end(), value);
	assert(result != columnsValues.end()); //Could not find given value's ID
	return result - columnsValues.begin();
}

std::vector<std::vector<int>> ACloseAlgorithm::GenerateTIDs()
{
	std::vector<std::vector<int>> tids{};
	//Allocate the necessary memory to hold the TIDs
	tids.resize(document.GetRowCount());
	for (auto& tid : tids)
	{
		tid.resize(document.GetColumnCount());
	}

	for (int i = 0; i < document.GetRowCount(); ++i)
	{
		auto row = document.GetRow<std::string>(i);
		for (int j = 0; j < row.size(); ++j)
		{
			tids[i][j] = GetID(row[j]);
		}
	}
	return tids;
}

void ACloseAlgorithm::GenerateTIds2()
{
	std::vector<std::vector<int>> tids{};
	//Allocate the necessary memory to hold the TIDs
	tids.resize(document.GetRowCount());
	for (auto& tid : tids)
	{
		tid.resize(document.GetColumnCount());
	}

	for (int iColumn = 0; iColumn < document.GetColumnCount(); ++iColumn)
	{
		//Get a column and find its unique values
		const auto column = document.GetColumn<std::string>(iColumn);
		for (int iRow = 0; iRow < document.GetColumnCount(); ++iRow)
		{
			//Check if the item already exists in the list of items, otherwise, add it 
			//(using an offset to skip searching items that belong to another column)
			const int offset = columnsValuesLastIndex.empty() ? 0 : columnsValuesLastIndex[iRow-1];
			if (std::find(columnsValues.begin() + offset, columnsValues.end(), column[iRow]) == columnsValues.end())
			{
				columnsValues
			}
		}
		//Save the last ID index of this column
		columnsValuesLastIndex.push_back(columnsValues.size() - 1);
	}
}



