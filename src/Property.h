# include <string>

using namespace std;

#include <iostream>
#include "CustomVector.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Class representing a property with various attributes
class Property {
public:
    int ads_id;                   // Unique listing id
    string prop_name;             // Name of the property
    int completion_year;          // Completion year of the property
    double monthly_rent;          // Monthly rent in RM
    string location;              // Property location in Kuala Lumpur region
    string property_type;         // Property type such as apartment, condominium, flat, duplex, studio etc
    int room;                     // Number of rooms in the unit
    int parking;                  // Number of parking space for the unit
    int bathroom;                 // Number of bathrooms in the unit
    double size;                  // Total area of the unit in square feet
    string furnished;             // Furnishing status of the unit (fully, partial, non-furnished)

    // Constructor to initialize property
    Property(int id, const string& name, int year, double rent, const string& loc,
             const string& type, int rms, int prk, int bath, double sz, const string& frn)
        : ads_id(id), prop_name(name), completion_year(year), monthly_rent(rent), location(loc),
          property_type(type), room(rms), parking(prk), bathroom(bath), size(sz), furnished(frn) {}

    // Display property details
    void display() const {
        cout << "-------------------------" << endl;
        cout << "Property ID: " << ads_id << endl;
        cout << "Name: " << prop_name << endl;
        cout << "Year of Completion: " << completion_year << endl;
        cout << "Monthly Rent: " << monthly_rent << endl;
        cout << "Location: " << location << endl;
        cout << "Property Type: " << property_type << endl;
        cout << "Rooms: " << room << endl;
        cout << "Parking Spaces: " << parking << endl;
        cout << "Bathrooms: " << bathroom << endl;
        cout << "Size: " << size << endl;
        cout << "Furnishing status: " << furnished << endl;
        cout << "-------------------------" << endl;
    }
};

class PropertyContainer {
private:
    Vlist<Property> properties;  // CustomVector to store properties

public:
    // Insert new property
    void insertProperty(const Property& prop) {
        properties.push_back(prop);
    }

    // Delete property by ID
    void deleteProperty(int ads_id) {
        for(size_t i = 0; i < properties.get_size(); ++i) {
            if (properties[i].ads_id == ads_id) {
                properties.erase(i);
                break;
            }
        }
        throw std::runtime_error("Property not found");
    }

    // Edit property by ID
    void editProperty(int ads_id, const Property& newProp) {
        for (Property& property : properties) {
            if (property.ads_id == ads_id) {
                property = newProp;
                break;
            }
        }
    }

    // Display all properties
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
                int completion_year = stoi(tokens[2]);
                double monthly_rent;
                if(tokens[3]!="0"){
                    monthly_rent = stod(tokens[3].substr(3)); 
                }else{
                    cout<<"fk u you piece of shit of a bug, you wasted 3 hours of my damn life that i could've used for sleep"<<endl;
                }
                string location = tokens[4];
                string property_type = tokens[5];
                if(tokens[6] == "More than 10"){
                    tokens[6] = "11";
                }
                int rooms = stoi(tokens[6]);
                int parking = stoi(tokens[7]);
                int bathroom = stoi(tokens[8]);
                double size = stod(tokens[9].substr(0, tokens[9].find(" sq.ft.")));
                string furnished_status = tokens[10];

                // Property object and add to vector
                Property property(ads_id, prop_name, completion_year, monthly_rent, location,
                              property_type, rooms, parking, bathroom, size, furnished_status);
                properties.push_back(property);
         } else {
            cerr << "Skipping line due to Insufficient data" << endl;
        }
    }

        file.close();
    }
};
