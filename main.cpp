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

/*void print_square_matrix(vector<vector<double> > matrix)
{
    cout << "------------------------------------------" << endl;
    for(int i = 0; matrix.size() != i; i++)
    {
        for(int j = 0; matrix.size() != j; j++)
        {

            cout << matrix[i][j] << "  ";
        }
        cout << "-" << endl;
    }
    cout << "------------------------------------------" << endl;
}*/

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
    ofstream myf;
    myf.open("idx_count.txt");
    for(int i = 0; 1 != i; i++)
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
        vector<double> comp_size;
        comp_size = truck1.assign_compartment_size();
        comp_size = truck2.assign_compartment_size();

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
        /*cars_to_be_sent.push_back(car9);
        cars_to_be_sent.push_back(car10);
        cars_to_be_sent.push_back(car11);
        cars_to_be_sent.push_back(car12);*/
        vector<Map> cities_for_ACO;
        vector<Map> cities;
        Map truck_origin = gothenburg;
        Map truck_destination = orebro;
        
        
        cities = truck1.get_cities_for_ACO(cars_to_be_sent, gothenburg, truck_destination);
        truck_destination.idx = cities.size();
        Map final_destination = truck_destination;
        


        // ACO
        // Origin
        //cities.push_back(alingsas);
        //cities.push_back(jonkoping);
        //cities.push_back(orebro);
        //cities.push_back(linkoping);
        //cities.push_back(uppsala);
        
        //cities.push_back(gothenburg);
        //cities.push_back(stockholm);
        //cities.push_back(stockholm);
        //cities.push_back(jonkoping);
        /*cities.push_back(ostersund);
        cities.push_back(lulea);
        cities.push_back(malmo);
        cities.push_back(pitea);*/
        //Map final_destination = linkoping;

        for(int i = 0; cities.size() != i; i++)
        {
            cout << cities[i].city_name << cities[i].idx << endl;
        }
        cout << "........" << endl;
        

        //alingsås, göteborg, stockholm, jonkoping verkar inte gå igenom korrekt, alldeles för snabbt och ingen förbättring

        int N = 5;


        //int max_idx = cities[0].find_max_idx(cities) + 1;
        //cout << "Maxxxx " << max_idx << endl;
        


        // Initialize tao0
        // Initialize tao0
        double nearest_neighbour_path_length = get_nearest_neighbour_path_length(cities);
        
        double tao0 = N/nearest_neighbour_path_length;
        //cout << "ssss" << tao0 << endl;
        double path_length;
        double evaporation_rate = 0.3;
        double best_path_length = INFINITY;
        int no_iterations = 1000;
        vector<Map> path;
        vector<Map> best_path;
        vector<double> path_length_collection;
        vector<vector<double> > tao_matrix = initialize_pheromone_matrix(tao0, cities.size());
        vector<Map> temp_cities = cities;
        temp_cities.push_back(final_destination);
        vector<vector<double> > delta_tao_matrix = initialize_delta_matrix(cities.size());
        /*path.push_back(linkoping);
        path.push_back(orebro);
        path.push_back(alingsas);
        path.push_back(gothenburg);
        path.push_back(jonkoping);
        path.push_back(uppsala);
        path.push_back(stockholm);*/
        //path.push_back(pitea);

        path_length = calculate_path_distance(cities, final_destination);

        //cout << "NNPL " << nearest_neighbour_path_length << endl;

        
        // Loop will go here
        for(int k = 0; no_iterations != k; k++)
        {    
            
            //
            //cout << "new_iter" << endl;

            delta_tao_matrix = initialize_delta_matrix(cities.size());
                
            
            //print_path(path);
            for(int i = 0; N != i; i++)
            {
                //print_path(path);
                path = build_path(tao_matrix, cities);
                path.push_back(final_destination); 
                path_length = calculate_path_distance(path,final_destination);
                //cout << "path_length" << endl;
                delta_tao_matrix = update_tao_for_ant(path_length,delta_tao_matrix, path, cities);
        
            }
            
            tao_matrix = vaporize(tao_matrix, delta_tao_matrix, evaporation_rate);
            path_length_collection.push_back(path_length);
            //print_square_matrix(tao_matrix);
            
            //vector<vector<double> > delta_tao_matrix = 
            //vector<vector<double> > delta_tao_matrix = initialize_delta_matrix(cities.size());
            //vector<vector<double> > delta_tao_matrix_update = initialize_delta_matrix(cities.size());
            
            if(best_path_length > path_length)
            {
                best_path_length = path_length;
                best_path = path;

            }
            if(k%1000 == 0)
            {
                cout << k << endl;
                cout << path_length << endl;
                cout << "best " << best_path_length << endl;
                //print_square_matrix(tao_matrix);
                
            }
        }
        cout << "Pathlength : "<< best_path_length << endl;
        cout << "Nearest path and coordinates based on " << no_iterations <<" iterations: " << endl;
        
        ofstream myfile;
        myfile.open("path.txt");
        for(int i = 0; path.size() != i; i++)
        {
            cout << best_path[i].x_coordinate <<", " <<
            best_path[i].y_coordinate << ", " << best_path[i].city_name << " idx "<< best_path[i].idx <<endl;
            myfile << best_path[i].x_coordinate <<", " <<
            best_path[i].y_coordinate << ", " << best_path[i].idx << endl;
            
        }

        for(int i = 0; path_length_collection.size() != i; i++)
        {
            myf << path_length_collection[i] << endl;
        }
        myf.close();
        myfile.close();

    truck1.print_truck();
    truck1.load_optimal_order(best_path, cars_to_be_sent); // BYT TILL BEST_PATH SEN
    truck1.print_truck();
    //truck1.print_loaded_cars();
    truck1.send_truck(orebro);
    truck1.print_loaded_cars();

    }
    
    /*truck1.print_truck();
    truck1.load_car(1, 2, comp_size, car1);
    truck1.load_car(1, 1, comp_size, car2);
    truck1.load_car(2, 1, comp_size, car3);
    truck1.load_car(2, 2, comp_size, car4);
    truck1.print_truck();
    truck1.print_loaded_cars();
    truck1.send_truck(stockholm);
    truck1.print_loaded_cars();
    truck1.print_truck();
    truck1.unload_car(car1);
    truck1.print_truck();
    truck1.send_truck(gothenburg);
    cout << car1.location.city_name << endl;
    cout << truck1.location_truck << endl;
    cout << car1.location.city_name << endl;*/


    
   
   
    return 0;
}



