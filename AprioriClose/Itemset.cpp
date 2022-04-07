#include "Itemset.h"
#include <algorithm>
#include <assert.h>

Itemset::Itemset(std::vector<std::pair<size_t, std::string>> items)
	:
	items(items),
	support(-1.f)
{
	assert(items.size() > 0);//Itemset needs to be composed of at least one item.
}

void Itemset::CalculateMetrics(const std::vector<std::map<std::string, std::vector<size_t>>>& tids, size_t rowCount)
{
	//The TID of this itemset is the intersection between the TID of all of its items.
	auto intersectedTID = tids[items[0].first].at(items[0].second);
	for (size_t i = 1; i < items.size(); ++i)
	{
		std::vector<size_t> temp;
		const std::vector<size_t>& otherTID = tids[items[i].first].at(items[i].second);

		std::set_intersection(intersectedTID.begin(), intersectedTID.end(),
			otherTID.begin(), otherTID.end(),
			back_inserter(temp));

		intersectedTID = std::move(temp);
	}
	//The support is simply the size of the TID of this itemset divided by the total row count.
	support = static_cast<float>(intersectedTID.size()) / rowCount;
}

float Itemset::GetSupport() const
{
	assert(support != -1.f); //Support metric has not been calculated yet.
	return support;
}

bool Itemset::HasFirstKInCommon(const Itemset& other, size_t k) const
{
	assert(items.size() >= k && other.items.size() >= k);//Both itemsets have to be longer or equal to k.
	bool inCommon = true;
	for (size_t i = 0; i < k; ++i)
	{
		if (items[i] != other.items[i])
		{
			inCommon = false;
			break;
		}
	}
	return inCommon;
}

bool Itemset::IsValid() const
{
	auto result = std::adjacent_find(items.begin(),
	items.end(),
	[](const std::pair<size_t, std::string>& first, const std::pair<size_t, std::string>& second) {
		return first.first == second.first;
		});

	return result == items.end();
}

Itemset Itemset::operator+(const Itemset& rhs) const
{
	std::vector<std::pair<size_t, std::string>> itemsUnion;
	std::set_union(
		items.begin(), items.end(),
		rhs.items.begin(), rhs.items.end(),
		std::back_inserter(itemsUnion)
	);
	return Itemset(itemsUnion);
}

