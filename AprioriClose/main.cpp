#include <rapidcsv.h> 
#include <iostream>
#include "ItemsetLoader.h"
#include "ACloseAlgorithm.h"

int main()
{
    //Load the airlines csv
    ItemsetLoader itemset{"airlines.csv"};
    
    //Apply discretization on the required columns
    itemset.Discretize<float>("Flight",10);
    itemset.Discretize<float>("Time",10);
    itemset.Discretize<float>("Length",10);

    ACloseAlgorithm algo{itemset.GetDocument()};
    //Save the new document to disk
    //itemset.SaveDocument("Airlines-discretized.csv");
}