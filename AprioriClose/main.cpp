#include <rapidcsv.h> 
#include <iostream>
#include "ItemsetLoader.h"
#include "ACloseAlgorithm.h"
#include "Timer.h"
int main()
{
    std::cout << "Loading csv ... ";
    Timer<std::chrono::milliseconds> timer{};
    //Load the airlines csv
    ItemsetLoader itemset{ "airlines.csv" };
    std::cout << "took " << timer.Mark() << " miliseconds\n";

    std::cout << "Discretizing ... ";
    timer.Mark();
    itemset.Discretize<float>({"Flight","Time","Length"},{10,10,10});
    std::cout << "took " << timer.Mark() << " miliseconds\n";

    std::cout << "Generating TIDs ... ";
    timer.Mark();
    ACloseAlgorithm algo{ itemset.GetDocument() };
    std::cout << "took " << timer.Mark() << " miliseconds\n";
    //Save the new document to disk
    //itemset.SaveDocument("Airlines-discretized.csv");
}