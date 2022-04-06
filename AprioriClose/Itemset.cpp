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
	if()
}

float Itemset::GetSupport() const
{
	assert(support != -1.f); //Support metric has not been calculated yet.
	return support;
}
