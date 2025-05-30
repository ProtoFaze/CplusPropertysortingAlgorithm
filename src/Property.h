#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Vlist.h"
#include "SortingAlgo1.h"
#include "SortingAlgo2.h"

using namespace std;

// Class representing a property with various attributes
struct Property {
public:
    static int objectCount;

    int ads_id;                   // Unique listing id
    string prop_name="0";             // Name of the property
    double monthly_rent=0;          // Monthly rent in RM
    int room=0;                     // Number of rooms in the unit

    // Constructor to initialize property
    Property(): ads_id(0), prop_name("0"), monthly_rent(0),room(0) {
            objectCount++;
    }

    Property(int id, const string& name, double rent, int rms)
        : ads_id(id), prop_name(name), monthly_rent(rent),room(rms) {
            objectCount++;
    }
    Property(const Property& new_prop) : ads_id(new_prop.ads_id), prop_name(new_prop.prop_name), monthly_rent(new_prop.monthly_rent), room(new_prop.room){
        objectCount++;
    }

    Property& operator=(const Property& newProp){
        ads_id = newProp.ads_id;
        prop_name = newProp.prop_name;
        monthly_rent = newProp.monthly_rent;
        room = newProp.room;
        return *this;
    }
    Property& operator=(Property&& newProp){
        ads_id = newProp.ads_id;
        prop_name = newProp.prop_name;
        monthly_rent = newProp.monthly_rent;
        room = newProp.room;
        return *this;
    }
    // Display property details
    void display() const {
        cout << "-------------------------" << endl;
        cout << "Property ID: " << ads_id << endl;
        cout << "Name: " << prop_name << endl;
        cout << "Monthly Rent: " << monthly_rent << endl;
        cout << "Rooms: " << room << endl;
        cout << "-------------------------" << endl;
    }

    string toCSVFormat() const {
        stringstream ss;
        ss << ads_id << "," << prop_name << "," << monthly_rent << "," << room;
        return ss.str();
    }
    ~Property(){
        objectCount--;
    }
};

class PropertyContainer{

private:
    std::shared_ptr<Vlist<Property>> properties;  // Shared pointer to CustomVector

public:
    PropertyContainer() : properties(std::make_shared<Vlist<Property>>()) {}

    // Return shared pointer to allow shared ownership
    std::shared_ptr<Vlist<Property>> getProperties() {
        return properties;
    }

    // Return const shared pointer to allow read-only shared ownership
    std::shared_ptr<const Vlist<Property>> getProperties() const {
        return properties;
    }

    // return a copy of the properties
    Vlist<Property> getPropertiesCopy() const {
        Vlist<Property> copy;
        for (const auto& property : *properties) {
            copy.emplaceBack(property);
        }
        return copy;
    }
    void setProperties(Vlist<Property> props) {
        cout<<"clearing properties"<<endl;
        properties->clear();
        if(properties->getSize() > 0){
            cout<<"data still exist, aborting"<<endl;
            return;
        }else{
            cout<<"data has been cleared, setting properties"<<endl;
            for(size_t i ; i< props.getSize(); i++){
                (*properties)[i] = std::move(props[i]);
            }
            cout<<"properties has been set"<<endl;
        }
    }
    

    void deleteProperty(int ads_id) {
        for(size_t i = 0; i < properties->getSize(); ++i) {
            if ((*properties)[i].ads_id == ads_id) {
                properties->erase(i);
                return;
            }
        }
        throw std::runtime_error("Property not found");
    }

    void editProperty(int ads_id, const Property& newProp) {
        for (auto& property : *properties) {
            if (property.ads_id == ads_id) {
                property = newProp;
                return;
            }
        }
        throw std::runtime_error("Property not found");
    }

    void displayProperties() const {
        for (const auto& property : *properties) {
            property.display();
            cout << endl;
        }
    }

    // Import from file
    void importFile(const string& filename) {
        ifstream file(filename); // Open file
        if (!file.is_open()) { // Check if the file opening is successful
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line; // Holds each line from the file
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            Vlist<string> tokens;
            //Check for String token with using quotations
            while (getline(ss, token, ',')) {
                if (token.front() == '"') {
                    string temp;
                    temp += token;
                    while (getline(ss, token, ',')) {
                        temp += token;
                        if (token.back() == '"') {
                            break;
                        }
                    }
                    tokens.pushBack(temp);
                } else if(token.empty()){
                    tokens.pushBack("0");
                } else{
                    tokens.pushBack(token);
                }
            }
            if (tokens.getSize() >= 4) { // Check if the line has enough tokens
                int ads_id = stoi(tokens[0]);
                string prop_name = tokens[1];
                double monthly_rent;
                if(tokens[3]!="0"){
                    tokens[3].erase(0, 3);// Remove RM prefix
                    int invalid_char_pos = tokens[3].find(" per month"); //remove per month suffix
                    tokens[3].replace(invalid_char_pos, 10, "");
                    //Remove thousanth spacer
                    int thousand_separator = tokens[3].find(" ");
                    if(thousand_separator != string::npos){
                        tokens[3].replace(thousand_separator, 1, "");
                    }
                    monthly_rent = stod(tokens[3]); 
                }
                if(tokens[6] == "More than 10"){
                    tokens[6] = "11";
                }
                int rooms = stoi(tokens[6]);

                // Property object and add to vector
                properties->emplaceBack(ads_id, prop_name, monthly_rent, rooms);
         } else {
            cerr << "Skipping line due to Insufficient data" << endl;
        }
    }

        file.close();
    }

    void writeToFile(const string& filePath){
        //open the file and write 
        ofstream file(filePath); // Open file
        if (!file.is_open()) { // Check if the file opening is successful
            cerr << "Error opening file: " << filePath << endl;
            return;
        }else{
            cout<<"writing to file"<<endl;
        }
        for(Property prop: *properties){
            file<<prop.toCSVFormat()<<endl;
        }
        file.close();
    }
    
    // void sorting_algo1(){
    //     tim_sort(*properties);
    // }

    // void sorting_algo2(){
    //     heapSort(*properties);
    // }
};
#endif