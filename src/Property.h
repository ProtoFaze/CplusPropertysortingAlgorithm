#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include "CustomVector.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Class representing a property with various attributes
struct Property {
public:
    static int objectCount;

    int ads_id;                   // Unique listing id
    string prop_name;             // Name of the property
    double monthly_rent;          // Monthly rent in RM
    int room;                     // Number of rooms in the unit

    // Constructor to initialize property
    Property(): ads_id(0), prop_name("0"), monthly_rent(0),room(0) {
            objectCount++;
        }

    Property(int id, const string& name, double rent, int rms)
        : ads_id(id), prop_name(name), monthly_rent(rent),room(rms) {
            objectCount++;
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
    Vlist<Property> properties;  // CustomVector to store properties

public:    

    Vlist<Property> getProperties() const {
        return properties;  
    }
    void setProperties(Vlist<Property> props) {
        properties.clear();
        if(properties.get_size() > 0){
            cout<<"data still exist, aborting"<<endl;
            return;
        }else{
            cout<<"data has been cleared, setting properties"<<endl;
            for(Property prop: props){
                properties.push_back(prop);
            }
        }
        // for(Property prop: props){
        //     properties.push_back(prop);
        // }

    }
    
    // Insert new property
    void insertProperty(const Property& prop) {
        properties.push_back(prop);
    }

    void deleteProperty(int ads_id) {
        for(size_t i = 0; i < properties.get_size(); ++i) {
            if (properties[i].ads_id == ads_id) {
                properties.erase(i);
                return;
            }
        }
        throw std::runtime_error("Property not found");
    }

    void editProperty(int ads_id, const Property& newProp) {
        for (auto& property : properties) {
            if (property.ads_id == ads_id) {
                property = newProp;
                return;
            }
        }
        throw std::runtime_error("Property not found");
    }

    void displayProperties() const {
        for (const auto& property : properties) {
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
                    tokens.push_back(temp);
                } else if(token.empty()){
                    tokens.push_back("0");
                } else{
                    tokens.push_back(token);
                }
            }
            if (tokens.get_size() >= 11) { // Check if the line has enough tokens
                int ads_id = stoi(tokens[0]);
                string prop_name = tokens[1];
                double monthly_rent;
                if(tokens[3]!="0"){
                    monthly_rent = stod(tokens[3].substr(3)); 
                }
                if(tokens[6] == "More than 10"){
                    tokens[6] = "11";
                }
                int rooms = stoi(tokens[6]);

                // Property object and add to vector
                properties.emplace_back(ads_id, prop_name, monthly_rent, rooms);
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
        for(Property prop: properties){
            file<<prop.toCSVFormat()<<endl;
        }
        file.close();
    }
};
#endif