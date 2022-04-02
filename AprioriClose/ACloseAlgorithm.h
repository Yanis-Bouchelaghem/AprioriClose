#pragma once
#include <vector>
#include <string>
#include "rapidcsv.h"

class ACloseAlgorithm
{
public:
	ACloseAlgorithm(const rapidcsv::Document& document);

private:

	void GenerateTIDs();
	int FindColumnValueID(const std::string& value, int column);
private:
	std::vector<std::vector<std::string>> valuesIndex;
	std::vector<std::vector<int>> tids;

	const rapidcsv::Document& document;
};