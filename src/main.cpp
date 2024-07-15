#include <iostream>
#include <typeinfo>
#include <chrono>
// #include "CustomVector.h"
// #include "Property.h"
#include "dataCleaning.h"
#include "Heap.h"


using namespace std;
using namespace std::chrono;

int Property::objectCount = 0;  // Definition of the static member
PropertyContainer container;

struct coords{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    coords(){}
    coords(float scalar) : x(scalar), y(scalar), z(scalar){}
    coords(float x, float y, float z) : x(x), y(y), z(z){}
    coords(const coords& other) : x(other.x), y(other.y), z(other.z){
        cout<<"copy constructor called"<<endl;
    }
    coords(coords&& other) : x(other.x), y(other.y), z(other.z){
        cout<<"move constructor called"<<endl;
    }
    ~coords(){
        cout<<"destructor called"<<endl;
    }
    coords& operator=(const coords& other){
        x = other.x;
        y = other.y;
        z = other.z;
        cout<<"copy assignment operator called"<<endl;
        return *this;
    }
    coords& operator=(coords&& other){
        x = other.x;
        y = other.y;
        z = other.z;
        cout<<"move assignment operator called"<<endl;
        return *this;
    }

};

// template <typename T>
// void PrintList(const Vlist<T>& list) {
//     for (size_t i = 0; i < list.get_size(); i++) {
//         cout << list[i] << endl;
//     }
//     cout << endl;
// }
// template <>
// void PrintList(const Vlist<coords>& list) {
//     for (size_t i = 0; i < list.get_size(); i++) {
//         cout << list[i].x << list[i].y << list[i].z << endl;
//     }
//     cout << endl;
// }

int cleanData() {
    cout << "--Cleaning Started--"<<endl;
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv");
    
    container.setProperties(clean::forwardFillEmpty(container.getProperties()));
    for(Property prop : container.getProperties()){
        if(prop.prop_name.find("@") != string::npos || prop.prop_name.find("–") != string::npos || prop.prop_name.find('"') != string::npos || prop.prop_name == "0" || prop.monthly_rent < 100 || prop.room < 1){
            cout<<prop.toCSVFormat()<<endl;
        }
    }
    cout<<"all supposedly invalid elements printed"<<endl;
    container.writeToFile(".././dataset/cleaned_prop_data.csv");
    cout << Property::objectCount << " property remaining before scope end" << endl;
    cout << "Cleaning Done" << endl;
    return 0;
}

int main(){
    cleanData();
    cout << "Heap Sort" << endl;
    int size = 0;
    std::vector<Property> props = container.getProperties();
    for(Property prop : props) {
        cout << prop.toCSVFormat() << endl;
        size++;
    }
    cout << "Size: " << size << endl;
    auto start = high_resolution_clock::now();
    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int N = sizeof(arr) / sizeof(arr[0]);
    heapSort(arr, N);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " seconds" << endl;
}