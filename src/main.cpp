#include <iostream>
#include <algorithm>
#include <chrono>
#include "dataCleaning.h"
#include "heapsort.h"

using namespace std;

int Property::objectCount = 0;  // Definition of the static member
PropertyContainer container; // create container

int cleanData() {
    cout << "--Cleaning Started--"<<endl;
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv");
    clean::forwardFillEmpty(container.getProperties().get());

    cout << Property::objectCount << " property remaining before scope end" << endl;
    cout << "Cleaning Done" << endl;
    return 0;
}

int main(){
    cleanData();
    Vlist<Property> prop = container.getPropertiesCopy();
    int size = prop.getSize();
    heapSort(prop, size, 2);
}