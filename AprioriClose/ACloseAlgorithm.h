#pragma once
#include <vector>
#include <string>
#include "rapidcsv.h"

class ACloseAlgorithm
{
public:
	ACloseAlgorithm(const rapidcsv::Document& document);
private:
	std::vector<std::string> itemIDs;
	std::vector<int> itemIndexes;
};