#include <iostream>
#include <algorithm>
#include <chrono>
#include "dataCleaning.h"
#include "heapsort.h"

using namespace std;
using namespace std::chrono;

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
    auto start = high_resolution_clock::now();
    heapSort(prop, size, 2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " seconds" << endl;
}