#include <iostream>
#include <algorithm>
#include <chrono>
#include "dataCleaning.h"

using namespace std;

int Property::objectCount = 0;  // Definition of the static member

int cleanData() {
    cout << "--program started--"<<endl;
    PropertyContainer container; // create container
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv"); //import data
    clean::forwardFillEmpty(container. getProperties().get()); //clean data

    cout << Property::objectCount << " property remaining before scope end" << endl; // check object count after operation
    cout << " program ended" << endl;
    return 0;
}

int main(){
    cleanData();
    
}