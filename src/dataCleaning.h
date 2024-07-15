#include "Property.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

namespace clean{
    string replaceInvalidChar(string str){
        cout << "Replace Invalid Char" << endl;


        
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

    void forwardFillEmpty(Vlist<Property> *properties) {
        cout << "Forward Fill" << endl;
        string last_prop_name = replaceInvalidChar((*properties)[0].prop_name);
        int last_room = (*properties)[0].room;
        double last_rent = (*properties)[0].monthly_rent;
        for (size_t i = 0; i < properties->getSize(); ++i) {
            if ((*properties)[i].ads_id == 0) {
                (*properties)[i].ads_id = (*properties)[i - 1].ads_id;
            }if ((*properties)[i].prop_name !="0") {
                last_prop_name = replaceInvalidChar((*properties)[i].prop_name);
            }
            (*properties)[i].prop_name = last_prop_name;
            if ((*properties)[i].monthly_rent >= 100) {
                last_rent = (*properties)[i].monthly_rent;
            }
            (*properties)[i].monthly_rent = last_rent;
            if ((*properties)[i].room < 1) {
                (*properties)[i].room = last_room;
            }
            last_room = (*properties)[i].room;
        }
    }


}