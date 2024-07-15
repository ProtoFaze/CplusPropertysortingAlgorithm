#include <iostream>
#include <algorithm>
#include "dataCleaning.h"

using namespace std;

int Property::objectCount = 0;  // Definition of the static member

int main(){
    cout << "--program started--"<<endl;
    PropertyContainer container; // create container
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv"); //import data
    clean::forwardFillEmpty(container.getProperties().get()); //clean data

    // container.sorting_algo1(); //run tim sort
    // container.sorting_algo2(); //run heap sort
    cout << Property::objectCount << " property remaining before scope end" << endl; // check object count after operation
    cout << " program ended" << endl;
    return 0;
}