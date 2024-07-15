#include <iostream>
#include <algorithm>
#include <chrono>
#include "dataCleaning.h"
#include "heapsort.h"

using namespace std;

int Property::objectCount = 0;  // Definition of the static member
PropertyContainer container; // create container

int cleanData() {
    cout << "--program started--"<<endl;
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv"); //import data
    clean::forwardFillEmpty(container. getProperties().get()); //clean data

    cout << Property::objectCount << " property remaining before scope end" << endl; // check object count after operation
    cout << " program ended" << endl;
    return 0;
}

int main(){
    cleanData();
    Vlist<Property> prop = container.getPropertiesCopy();
    int size = prop.getSize();
    heapSort(prop, size, 2);
}