#include "Itemset.h"
#include <algorithm>
#include <assert.h>

Itemset::Itemset(std::vector<std::pair<size_t, size_t>> items, const std::vector<std::vector<size_t>>& tids)
	:
	items(items),
	tids(tids),
	support(-1.f)
{
}

void Itemset::CalculateMetrics()
{
	size_t supportCount = 0;
	for (const auto& tid : tids)
	{
		//Check if tid matches the items
		bool matches = std::all_of(items.begin(), items.end(), [tid](const std::pair<size_t,size_t>& item) {
				return tid[item.first] == item.second;
			});
		if (matches)
		{
			++supportCount;
		}
	}
	support = static_cast<float>(supportCount) / tids.size();
}

float Itemset::GetSupport() const
{
	assert(support != -1.f); //Support metric has not been calculated yet.
	return support;
}
