#include "Itemset.h"
#include <algorithm>
#include <assert.h>

Itemset::Itemset(std::vector<std::pair<size_t, std::string>> items, const std::vector<std::map<std::string, std::vector<size_t>>>& tids, const rapidcsv::Document& document)
	:
	items(items),
	tids(tids),
	document(document),
	support(-1.f)
{
	assert(items.size() > 0);//Items cannot be empty.
}

void Itemset::CalculateMetrics()
{
	if (items.size() == 1)
	{
		support = static_cast<float>(tids[items[0].first].at(items[0].second).size()) / document.GetRowCount();
	}
	else
	{
		//Intersect between the TID of the items
		auto intersection = tids[items[0].first].at(items[0].second);
		for (size_t i = 1; i < items.size(); ++i)
		{
			std::vector<size_t> temp;
			const std::vector<size_t>& otherTID = tids[items[i].first].at(items[i].second);

			std::set_intersection(intersection.begin(), intersection.end(),
				otherTID.begin(), otherTID.end(),
				back_inserter(temp));

			intersection = std::move(temp);
		}
		support = static_cast<float>(intersection.size()) / document.GetRowCount();
	}
}

float Itemset::GetSupport() const
{
	assert(support != -1.f); //Support metric has not been calculated yet.
	return support;
}
