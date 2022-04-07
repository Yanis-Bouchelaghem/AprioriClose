#pragma once
#include <vector>
#include <map>
#include <string>
#include "rapidcsv.h"

class Itemset
{
public:
	Itemset(std::vector<std::pair<size_t, std::string>> items);
	void CalculateMetrics(const std::vector<std::map<std::string, std::vector<size_t>>>& tids, size_t rowCount);
	float GetSupport() const;
	bool HasFirstKInCommon(const Itemset& other, size_t k) const;
	bool IsValid() const;
	Itemset operator +(const Itemset& rhs) const;
private:
	float support;
	std::vector<std::pair<size_t,std::string>> items;
};