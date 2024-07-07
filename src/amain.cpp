#include <iostream>
// #include "CustomVector.h"
#include "Property.h"
using namespace std;

int main(){
    cout << "--program started--"<<endl;
    PropertyContainer container;
    container.importFile(".././dataset/mudah-apartment-kl-selangor.csv");
    container.displayProperties();
    // Vlist<int> vec = {1, 2, 3, 4, 5};
    // vec.push_back(6);
    // vec.push_back(7);

    // for (auto *it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // vec.erase(2); // Remove element at index 2

    // for (auto *it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // vec.insert(2, 99); // Insert 99 at index 2

    // for (auto *it = vec.begin(); it != vec.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    // return 0;
}