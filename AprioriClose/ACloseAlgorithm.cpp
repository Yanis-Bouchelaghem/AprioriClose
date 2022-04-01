#include "ACloseAlgorithm.h"
#include <string>
#include <algorithm>

ACloseAlgorithm::ACloseAlgorithm(const rapidcsv::Document& document)
{
	for (int i = 0; i < document.GetColumnCount(); ++i)
	{
		//Get a column and find its unique values
		const auto column = document.GetColumn<std::string>(i);
		for (const auto& value : column)
		{
			//Check if the item already exists in the list of items, otherwise, add it 
			//(using an offset to skip searching items that belong to another column)
			int offset = itemIndexes.empty() ? 0 : (itemIndexes[i - 1] + 1);
			if (std::find(itemIDs.begin() + offset, itemIDs.end(), value) == itemIDs.end())
			{
				itemIDs.emplace_back(value);
			}
		}
		//Save the last ID index of this column
		itemIndexes.push_back(itemIDs.size()-1);
	}
}
