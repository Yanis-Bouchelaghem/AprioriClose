#include <rapidcsv.h> 
#include <iostream>
#include "ItemsetLoader.h"

int main()
{
    ItemsetLoader itemset{"airlines.csv"};
    
    itemset.Discretize<float>("Flight",10);
    itemset.Discretize<float>("Time",10);
    itemset.Discretize<float>("Length",10);
    itemset.SaveDocument("Airlines-discretized.csv");
}