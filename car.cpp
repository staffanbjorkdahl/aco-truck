#include <string>
#include "car.h"

        Car::Car(double length, double height, double weight, Map location, Map destination, std::string reg_no)
        {
            this->length = length;
            this->height = height;
            this->reg_no = reg_no;
            this->location = location;
            this->destination = destination;
            this->weight = weight;  
        }
