#pragma once
#include <vector>


class Itemset
{
public:
	Itemset(std::vector<std::pair<size_t, size_t>> items, const std::vector<std::vector<size_t>>& tids);
	void CalculateMetrics();
	float GetSupport() const;
private:
	float support;
	std::vector<std::pair<size_t,size_t>> items;
	const std::vector<std::vector<size_t>>& tids;
};