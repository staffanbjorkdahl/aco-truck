#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include <fstream>
#include "map.h"
#include "car.h"
#include "truck.h"
#include "AntColonyOptimization.h"

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::find;
using namespace std;

void print_path(vector<Map> p)
{
    cout << "-------print_path" << endl;
    for(int i = 0; p.size() != i; i++)
    {
        cout << p[i].city_name << p[i].idx << " ";
    }
    cout << " " << endl;
    cout << "------print_path end" << endl;
}

int main()
{
    // Build up the map
    vector<int> best_idx_coll;    
    Map alingsas(57.9294796,12.5054877, "Alingsas",0);
    Map gothenburg(57.7006826,11.6136583, "Gothenburg",1);
    Map stockholm(59.3260668,17.8390018, "Stockholm",2);
    Map jonkoping(57.7559198,14.0481715,"Jonkoping",3);
    Map linkoping(58.4037121,15.4706911, "Linkoping",4);
    Map orebro(59.2780547,15.1324149, "Orebro",5);
    Map uppsala(59.8332051,17.5183649,"Uppsala",6);
    Map pitea(65.3049443,21.4091559,"Pitea",7);
    Map ostersund(63.175284,14.5107019,"Ostersund",8);
    Map lulea(65.5865976,22.0422997,"Lulea",9);
    Map malmo(55.5700886,12.8758894,"Malmo",10);
    Map umea(63.8268562,20.1018802,"Umea",11);
    
    // Trucks
    Truck truck1(1, 8, 40000);
    Truck truck2(2, 8, 30000);

    // Cars
    Car car1(1.6, 3.4, 1800, gothenburg, alingsas, "ELI935");
    Car car2(1, 3, 1750, gothenburg, stockholm, "STA929");
    Car car3(2.5, 4, 2500, gothenburg, jonkoping, "CPA673");
    Car car4(2, 4, 2500, gothenburg, umea, "AYC775");
    Car car5(2, 4, 2500, gothenburg, stockholm, "MLB040");
    Car car6(2, 4, 2500, gothenburg, ostersund, "MLB050");
    Car car7(2, 4, 2500, gothenburg, malmo, "MLB030");
    Car car8(2, 4, 2500, gothenburg, orebro, "MLB020");
    Car car9(2, 4, 2500, gothenburg, pitea, "MLB021");
    Car car10(2, 4, 2500, gothenburg, lulea, "MLB022");
    Car car11(2, 4, 2500, gothenburg, umea, "MLB023");
    Car car12(2, 4, 2500, gothenburg, uppsala, "MLB024");

    vector<Car> cars_to_be_sent;
    cars_to_be_sent.push_back(car1);
    cars_to_be_sent.push_back(car2);
    cars_to_be_sent.push_back(car3);
    cars_to_be_sent.push_back(car4);
    cars_to_be_sent.push_back(car5);
    cars_to_be_sent.push_back(car6);
    cars_to_be_sent.push_back(car7);
    cars_to_be_sent.push_back(car8);
    
    Map truck_origin = gothenburg;
    Map truck_destination = orebro;
    vector<Map> cities;

    cities = truck1.get_cities_for_ACO(cars_to_be_sent, truck_origin, truck_destination);
    truck_destination.idx = cities.size();

    int const NO_ANTS = 5; 
    int const NO_ITERATIONS = 2;
    double const EVAPORATION_RATE = 0.3;
    double nearest_neighbour_path_length = get_nearest_neighbour_path_length(cities);
    double tao0 = NO_ANTS/nearest_neighbour_path_length;
    double path_length;
    double best_path_length = INFINITY;
    
    vector<Map> path;
    vector<Map> best_path;
    vector<double> path_length_collection;
    vector<vector<double> > tao_matrix = initialize_pheromone_matrix(tao0, cities.size());
    vector<vector<double> > delta_tao_matrix = initialize_delta_matrix(cities.size());

    // ACO loop
    path_length = calculate_path_distance(cities, truck_destination);
    for(int k = 0; NO_ITERATIONS != k; k++)
    {    
        delta_tao_matrix = initialize_delta_matrix(cities.size()); //New delta matrix for every new iteration initialized to zeros
        for(int i = 0; NO_ANTS != i; i++)
        {
            path = build_path(tao_matrix, cities); // Build the path this ant takes
            path.push_back(truck_destination); // Make sure the destination is the last in the path
            path_length = calculate_path_distance(path,truck_destination);
            delta_tao_matrix = update_tao_for_ant(path_length,delta_tao_matrix, path); // Create the delta matrix
        }
        tao_matrix = vaporize(tao_matrix, delta_tao_matrix, EVAPORATION_RATE); //Update the matrix 
        
        path_length_collection.push_back(path_length);            
        if(best_path_length > path_length)
        {
            best_path_length = path_length;
            best_path = path;
        }
        if(k%1000 == 0)
        {
            cout << "Best current path: " << best_path_length << endl;
        }
    }
    cout << "Path length : "<< best_path_length << endl;
    cout << "Shortest path and coordinates based on " << NO_ITERATIONS << " iterations: " << endl;
    ofstream myfile;
    myfile.open("path.txt");
    for(int i = 0; path.size() != i; i++)
    {
        cout << best_path[i].x_coordinate <<", " <<
        best_path[i].y_coordinate << ", " << best_path[i].city_name << " idx "<< best_path[i].idx <<endl;
        myfile << best_path[i].x_coordinate <<", " <<
        best_path[i].y_coordinate << ", " << best_path[i].idx << endl;   
    }
    
    myfile.close();

    truck1.print_truck();
    truck1.load_optimal_order(best_path, cars_to_be_sent);
    truck1.print_truck();
    truck1.send_truck(orebro);
    truck1.print_loaded_cars();
    return 0;
}



