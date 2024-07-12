#include <iostream>
// #include "CustomVector.h"
// #include "Property.h"
#include "dataCleaning.h"

using namespace std;

int Property::objectCount = 0;  // Definition of the static member
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

int main(){
    cout << "--program started--"<<endl;
    PropertyContainer container;
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv");
    
    shared_ptr<Vlist<Property>> props = container.getProperties();
    clean::forwardFillEmpty(props.get());
    cout<<"printing supposedly invalid elements"<<endl;
    for(Property prop : *props){
        if(prop.prop_name.find("@") != string::npos || prop.prop_name.find("–") != string::npos || prop.prop_name.find('"') != string::npos || prop.prop_name == "0" || prop.monthly_rent < 100 || prop.room < 1){
            cout<<prop.toCSVFormat()<<endl;
        }
        if(prop.prop_name.find("Pavilion") != string::npos){
            cout<<prop.toCSVFormat()<<endl;
        }
    }
    cout<<"all supposedly invalid elements printed"<<endl;
    // clean::forwardFillEmpty(container.properties);

    // cout << Property::objectCount << " property remaining after cleaning" << endl;
    // container.writeToFile(".././dataset/cleaned_prop_data.csv");
    cout << Property::objectCount << " property remaining before scope end" << endl;
    cout << " program ended" << endl;
    return 0;
}