#include <iostream>
#include <algorithm>
#include <chrono>
#include "dataCleaning.h"
#include "heapsort.h"
#include "timsort.h"

using namespace std;
using namespace std::chrono;

int Property::objectCount = 0;  // Definition of the static member
PropertyContainer container; // create container

int cleanData() {
    cout << "--Cleaning Started--"<<endl;
    container.importClean(".././dataset/cleaned_prop_data.csv");
    clean::forwardFillEmpty(container.getProperties().get());

    cout << Property::objectCount << " property remaining before scope end" << endl;
    cout << "Cleaning Done" << endl;
    return 0;
}

int main(){
    cleanData();
    Vlist<Property> prop = container.getPropertiesCopy();
    cout << string(15, '-') << "Heap Sort" << string(15, '-') << endl;
    int size = prop.getSize();
    auto start = high_resolution_clock::now();
    heapSort(prop, size, 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by heap: " << duration.count() << "ms" << endl;

    cout << string(15, '-') << "Tim Sort" << string(15, '-') << endl;

    start = high_resolution_clock::now();
    timSort(prop, size, 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by tim: " << duration.count() << "ms" << endl;
}