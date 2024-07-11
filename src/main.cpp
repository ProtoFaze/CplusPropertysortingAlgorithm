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
    
    // container.setProperties(clean::forwardFillEmpty(container.getProperties()));
    vector<Property> clean = clean::forwardFillEmpty(container.getProperties());
    for(Property prop : clean){
        if(prop.monthly_rent < 100 || prop.room < 0 || prop.prop_name == "0" || prop.ads_id == 0){
            cout<<prop.toCSVFormat()<<endl;
        }
    }
    cout<<"all supposedly invalid elements printed"<<endl;
    container.writeToFile(".././dataset/cleaned_prop_data.csv");
    cout << Property::objectCount << " property remaining before scope end" << endl;
    cout << " program ended" << endl;
    // Vlist<coords> list;
    // list.emplace_back(1.0f);
    //     PrintList(list);
    // list.emplace_back(1, 5, 9);
    //     PrintList(list);
    // list.emplace_back(1, 9, 7);
    //     PrintList(list);
    // list.emplace_back();
    // PrintList(list);
    // list.pop_back();
    // list.pop_back();
    // PrintList(list);
    // list.emplace_back(7, 3, 8);
    // list.emplace_back();
    // PrintList(list);
    // list.clear();
    // PrintList(list);
    // list.emplace_back(1, 5, 9);
    // list.emplace_back(1, 9, 7);
    // PrintList(list);
    return 0;
}