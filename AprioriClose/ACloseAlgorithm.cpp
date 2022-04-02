#include "ACloseAlgorithm.h"
#include <string>
#include <algorithm>

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
{
	GenerateAllColumnsValues(document);
}

void ACloseAlgorithm::GenerateAllColumnsValues(const rapidcsv::Document& document)
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
