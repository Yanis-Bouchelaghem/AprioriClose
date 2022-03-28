#pragma once
#include <rapidcsv.h>
#include <string>
#include <vector>
#include <format>
#include <functional>

/*
* @brief Class that handles loading csv files and provides preprocessing tools on the data
* (such as discretization).
*/
class ItemsetLoader
{
public:
	/*
	* @brief Constructor.
	* @param path : The name or path of the csv file to read.
	*/
	ItemsetLoader(const std::string& path)
		:
		document(path)
	{
	}
	/*
	* @brief Writes the current state of the document to disk.
	* @param path : The name or path to write to.
	*/
	void SaveDocument(const std::string& path)
	{
		document.Save(path);
	}

public:
	
	/**
	 * @brief Applies Equal-Width discretization on the specified column using the given number of bins.
	 * @tparam T : The type used to interpret the values of the column.
	 * @param columnName : The name of the column to discretize.
	 * @param binNumber : The number of bins to equally divide the data into.
	*/
	template<typename T>
	void Discretize(const std::string& columnName, unsigned int binNumber)
	{
		assert(binNumber != 0); //Bin number cannot be 0
		//Get the corresponding column
		auto column = document.GetColumn<T>(columnName);
		//Find the min and the max values of the column
		auto MinMaxElements = std::minmax_element(column.begin(), column.end());
		const T min = *MinMaxElements.first;
		const T max = *MinMaxElements.second;
		//Calculate the step
		const T step = float((max - min) / binNumber);
		//Generate the bins
		std::vector<std::pair<T, T>> bins;
		for (unsigned int i = 0; i < binNumber; ++i)
		{
			bins.emplace_back(min+step*i, min+step*(i+1));
		}
		//Create the string representation of each bin
		std::vector<std::string> binsText;
		for (unsigned int i = 0; i < binNumber-1; ++i)
		{
			binsText.emplace_back(std::format("[{:.2f}-{:.2f})", bins[i].first, bins[i].second));
		}
		binsText.emplace_back(std::format("[{:.2f}-{:.2f}]", bins[binNumber-1].first, bins[binNumber-1].second));
		//Replace the discrete values with the bin they belong to
		std::vector<std::string> binnedValues;
		binnedValues.reserve(column.size());
		for (const auto& value : column)
		{
			const auto correspBinIndex = std::min((unsigned int)((value - min) / step), binNumber-1);
			binnedValues.push_back(binsText[correspBinIndex]);

		}
		//Commit the changes to the document
		document.SetColumn(columnName,binnedValues);
	}
private:
	rapidcsv::Document document;
};

