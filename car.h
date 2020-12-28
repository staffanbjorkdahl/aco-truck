#ifndef CAR_H
#define CAR_H
#include <string>
#include "map.h"
using std::string;

class Car
{
    public:
        double length;
        double height;
        int weight;
        string reg_no;
        int y_position;
        int x_position;
        Map destination;
        Map location;
        Car(double length, double height, double weight, Map location, Map destination, string reg_no);
        //Car(){}
};
#endif