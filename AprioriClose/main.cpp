#include <rapidcsv.h> 
#include <iostream>
#include "DocumentLoader.h"
#include "ACloseAlgorithm.h"
#include "Itemset.h"
#include "Timer.h"
int main()
{
    std::cout << "Loading csv ... ";
    Timer<std::chrono::milliseconds> timer{};
    //Load the airlines csv
    DocumentLoader itemset{ "airlines.csv" };
    std::cout << "took " << timer.Mark() << " miliseconds\n";

    std::cout << "Discretizing ... ";
    timer.Mark();
    itemset.Discretize<float>({"Flight","Time","Length"},{10,10,10});
    std::cout << "took " << timer.Mark() << " miliseconds\n";

    std::cout << "Generating TIDs ... ";
    timer.Mark();
    ACloseAlgorithm algo{ itemset.GetDocument() };
    std::cout << "took " << timer.Mark() << " miliseconds\n";

    std::cout << "Generating itemsets ...\n";
    timer.Mark();
    algo.Go(0.005f);
    std::cout << "\nk-itemsets generation took " << timer.Mark() << " miliseconds.\n";
    algo.PrintItemsets();
    std::cout << std::endl;
    //Save the new document to disk
    //itemset.SaveDocument("Airlines-discretized.csv");
}