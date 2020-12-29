#ifndef TRUCK_H
#define TRUCK_H 
#include <string>
#include <vector>
#include <iostream>
#include "map.h"
#include "car.h"

using std::cout; using std::endl;


class Truck
{
    public:
        int truck_no;
        int truck_size;
        int variant;
        int max_load;
        int allowed_weight;
        std::string location_truck;
        std::string truck_origin;
        std::string truck_destination;
        std::vector<std::vector<int> > tot_comp_positions;
        std::vector<Car> loaded_cars;
        
        Truck(int truck_no, int size, int max_load, std::string location_truck = "default_Gothenburg");
        std::vector<double > assign_compartment_size();
        void print_truck();
        void load_car(int pos_y, int pos_x, Car car);
        void unload_car(Car &car);
        void send_truck(Map destination);
        void print_loaded_cars();
        void load_optimal_order(std::vector<Map> best_path, std::vector<Car> cars_to_be_sent);
        std::vector<Map> get_cities_for_ACO(std::vector<Car> cars_collection, Map truck_origin, Map truck_destination);

};
#endif
//test comment for git here and now what the fuck