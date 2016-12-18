#include "datatilepropertys.h"



sf::Color PropertyValue::as_color(){
    if (tType == STRING_E){
        string *tempFullStr = static_cast<string*>(vData);

        if ((*tempFullStr)[0] != '#'){
            return sf::Color(255, 255, 255, 255);
        } else {
            unsigned colors[4]; // 1 - red; 2 - green; 3 - blue; 0 - opacity;

            unsigned tempUint = 0;

            int counter = 0;
            int pos = 0, stepen = 1;
            for (char i : *tempFullStr){
                if (i != '#'){
                    counter++;
                    tempUint += charHexToUInt(i) * pow(16, stepen);
                    stepen--;
                }
                if (counter == 2){
                    counter = 0;
                    colors[pos] = tempUint;
                    tempUint = 0;
                    pos++;
                    stepen = 1;
                }
            }

            return sf::Color(colors[1], colors[2], colors[3], colors[0]);
        }

    }

    return sf::Color(255, 255, 255, 255);
}

sf::Uint8 PropertyValue::charHexToUInt(char c){
    switch (c){
    case 'F': case 'f': return 15;
    case 'E': case 'e': return 14;
    case 'D': case 'd': return 13;
    case 'C': case 'c': return 12;
    case 'B': case 'b': return 11;
    case 'A': case 'a': return 10;
    }
    return static_cast<sf::Uint8>(atoi(&c));
}

bool PropertyValue::as_bool(){
    if (tType == BOOL_E){
        bool *temp = static_cast<bool*>(vData);
        return *temp;
    }

    if (tType == STRING_E){
        string *temp = static_cast<string*>(vData);
        if (strcmp(temp->c_str(), "true") == 0){
            return true;
        } else if (strcmp(temp->c_str(), "false") == 0){
            return false;
        }

        if (strcmp(temp->c_str(), "1") == 0){
            return true;
        } else if (strcmp(temp->c_str(), "0") == 0){
            return false;
        }

        if (temp->size() > 0){
            return true;
        } else {
            return false;
        }
    }

    if (tType == INT_E){
        int *temp = static_cast<int*>(vData);
        if (*temp >= 1){
            return true;
        } else {
            return false;
        }
    }

    if (tType == FLOAT_E){
        float *temp = static_cast<float*>(vData);
        if (static_cast<int>(*temp) >= 1){
            return true;
        } else {
            return false;
        }
    }

    return false;
}

string PropertyValue::as_string(){
    if (tType == STRING_E){
        string *temp = static_cast<string*>(vData);
        return *temp;
    }

    std::ostringstream str;
    if (tType == FLOAT_E) {
        str << *(static_cast<float*>(vData));
        return str.str();
    } else if (tType == INT_E){
        str << *(static_cast<int*>(vData));
        return str.str();
    } else if (tType == BOOL_E){
        str << *(static_cast<bool*>(vData));
        return str.str();
    } else {
        return string("error type");
    }
}

float PropertyValue::as_float(){
    if (tType == FLOAT_E){
        float *temp = static_cast<float*>(vData);
        return *temp;
    } else if (tType == INT_E){
        int *temp = static_cast<int*>(vData);
        return static_cast<float>(*temp);
    } else if (tType == BOOL_E){
        bool *temp = static_cast<bool*>(vData);
        return static_cast<float>(*temp);
    } else if (tType == STRING_E){
        double temp = atof( static_cast<string*>(vData)->c_str() );
        return static_cast<float>(temp);
    } else {
        return 0;
    }
}

int PropertyValue::as_int(){
    if (tType == INT_E){
        int *temp = static_cast<int*>(vData);
        return *temp;
    } else if (tType == BOOL_E){
        bool *temp = static_cast<bool*>(vData);
        return static_cast<int>(*temp);
    } else if (tType == STRING_E){
        int temp = atoi( static_cast<string*>(vData)->c_str() );
        return temp;
    } else if (tType == FLOAT_E) {
        float *temp = static_cast<float*>(vData);
        return static_cast<int>(*temp);
    } else {
        return 0;
    }
}

void PropertyValue::operator=(int value){
    newData<int>(value);
    tType = INT_E;
}

void PropertyValue::operator=(float value){
    newData<float>(value);
    tType = FLOAT_E;
}

void PropertyValue::operator=(string value){
    newData<string>(value);
    tType = STRING_E;
}

/*void DataTilePropertys::operator=(bool value){
    newData<bool>(value);
    tType = BOOL_E;
}*/

void PropertyValue::operator=(sf::Color value){
    newData<sf::Color>(value);
    tType = COLOR_E;
}

template <class T>
void PropertyValue::newData(T value){
    deleteCurrentData();
    T *temp = new T(value);
    vData = static_cast<void*>(temp);
}

void PropertyValue::deleteCurrentData(){
    if (vData != nullptr){
        if (tType == INT_E){
            delete static_cast<int*>(vData);
        }
        if (tType == FLOAT_E){
            delete static_cast<float*>(vData);
        }
        if (tType == STRING_E){
            delete static_cast<string*>(vData);
        }
        if (tType == BOOL_E){
            delete static_cast<bool*>(vData);
        }
        if (tType == COLOR_E){
            delete static_cast<sf::Color*>(vData);
        }
    }

    vData = nullptr;
}

PropertyValue::PropertyValue(){
    vData = nullptr;
    tType = NONE_E;
}

PropertyValue::~PropertyValue(){
    deleteCurrentData();
}
