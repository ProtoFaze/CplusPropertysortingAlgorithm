// #include "Property.h"
#include "Property copy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace clean{
    string replaceInvalidChar(string str){
        if (str.find("–")!= string::npos){ 
            //replace the character with a hyphen
            int invalid_char_pos = str.find("–");
            str.replace(invalid_char_pos, 3, "-");
        }
        if (str.find("@")!= string::npos){ 
            //replace the character with @ symbol
            int at_symbol_pos = str.find("@");
            str.replace(at_symbol_pos, 1, "-");
        }
        if (str.find('"')!= string::npos){ 
            //trim the quotation marks
            str = str.substr(1, str.size()-2);
        }
        return str;
    }

    // Vlist<Property> forwardFillEmpty(Vlist<Property> properties) {
    //     string last_prop_name = properties[0].prop_name;
    //     int last_room = properties[0].room;
    //     double last_rent = properties[0].monthly_rent;
    //     for (size_t i = 1; i < properties.get_size(); ++i) {
    //         if (properties[i].ads_id == 0) {
    //             properties[i].ads_id = properties[i - 1].ads_id;
    //         }if (properties[i].prop_name =="0") {
    //             properties[i].prop_name = last_prop_name;
    //         }else{
    //             last_prop_name = replaceInvalidChar(properties[i].prop_name);
    //         }if (properties[i].monthly_rent < 100) {
    //             properties[i].monthly_rent = last_rent;
    //         }else{
    //             last_rent = properties[i].monthly_rent;
    //         }if (properties[i].room < 0) {
    //             properties[i].room = last_room;
    //         }else {
    //             last_room = properties[i].room;
    //         }
    //     }
    //     return properties;
    // }

    vector<Property> forwardFillEmpty(vector<Property> properties) {
        string last_prop_name = replaceInvalidChar(properties[0].prop_name);
        int last_room = properties[0].room;
        double last_rent = properties[0].monthly_rent;
        for (size_t i = 0; i < properties.size(); ++i) {
            if (properties[i].ads_id == 0) {
                properties[i].ads_id = properties[i - 1].ads_id;
            }if (properties[i].prop_name !="0") {
                last_prop_name = replaceInvalidChar(properties[i].prop_name);
            }
            properties[i].prop_name = last_prop_name;
            if (properties[i].monthly_rent >= 100) {
                last_rent = properties[i].monthly_rent;
            }
            properties[i].monthly_rent = last_rent;
            if (properties[i].room < 1) {
                properties[i].room = last_room;
            }
            last_room = properties[i].room;
        }
        return properties;
    }

    vector<Property> dropInvalid(vector<Property> properties){
        vector<Property> new_properties;
        for(Property prop : properties){
            if(prop.monthly_rent > 100 & prop.room > 0 & prop.prop_name == "0" & prop.ads_id == 0){
                new_properties.push_back(prop);
            }
        }
        return properties;
    }
}