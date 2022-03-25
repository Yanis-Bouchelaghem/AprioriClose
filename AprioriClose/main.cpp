#include <rapidcsv.h> 
#include <iostream>
#include "ItemsetLoader.h"

int main()
{
    ItemsetLoader itemset{"airlines.csv"};
    
    itemset.Discretize<double>("Flight",10);
    itemset.Discretize<double>("Time",10);
    itemset.Discretize<double>("Length",10);
    itemset.SaveDocument("Airlines-discretized.csv");
}