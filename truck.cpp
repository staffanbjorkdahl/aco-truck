#include <string>
#include <vector>
#include <string>
#include <set>
#include <iostream>
#include "truck.h"
#include "map.h"
#include "car.h"

using std::cout; using std::endl;




        Truck::Truck(int truck_no, int truck_size, int max_load, std::string location_truck)
        {
            this->truck_no = truck_no;
            this->truck_size = truck_size;
            this->max_load = max_load;
            this->location_truck = location_truck;
            this->loaded_cars = loaded_cars;
            this->allowed_weight = max_load;   
        };

        void Truck::print_truck()
        {
            std::string cab_top = "  __ ";
            std::string cab_middle1 = " /  | ";
            std::string cab_middle2 = " ––– ";
            std::string cab_bottom1 = "|   |";
            std::string cab_bottom2 = " –––  ";
            std::string wheel = "  o";
            std::string cab_width(cab_bottom2.size()/2-1, ' ');

            std::string compartment_top = " –––––";
            std::string compartment_bottom = " –––––";
            std::string delimiter = "|";
            std::string space(4,' ');
            std::string space_occupied = "  x ";
            std::string space_delimiter = delimiter + space + delimiter;
            std::string space_delimiter_occupied = delimiter + space_occupied + delimiter;
            std::string temp1, temp2, temp3, temp4, temp5, temp6;

            int count_occu1 = 1;
            int count_occu2 = 1;
            int count_occu_top = 0;
            int count_occu_bottom = 0;

            // Sort the compartment positions
            std::vector<int> temp_vector_top_floor;
            std::vector<int> temp_vector_bottom_floor;

            for(int i = 0; i != tot_comp_positions.size(); i++)
            {
                if(tot_comp_positions[i][0] == 1)
                {
                    temp_vector_top_floor.push_back(tot_comp_positions[i][1]);
                }
                if(tot_comp_positions[i][0] == 2)
                {
                    temp_vector_bottom_floor.push_back(tot_comp_positions[i][1]);
                }

            }

            sort(temp_vector_top_floor.begin(), temp_vector_top_floor.end());  
            sort(temp_vector_bottom_floor.begin(), temp_vector_bottom_floor.end());   

            //Arrange the sorted positions such that it fits the build up of the printing
            std::vector<std::vector<int> > tot_comp_positions_temp;
            std::vector<int> temp_vector_top_floor_for_sorting;
            for(int i = 0; i != temp_vector_top_floor.size(); i++)
            {
                temp_vector_top_floor_for_sorting.push_back(1); // Top floor
                temp_vector_top_floor_for_sorting.push_back(temp_vector_top_floor[i]);
                tot_comp_positions_temp.push_back(temp_vector_top_floor_for_sorting);
                temp_vector_top_floor_for_sorting.clear();
            }
            std::vector<int> temp_vector_bottom_floor_for_sorting;
            for(int i = 0; i != temp_vector_bottom_floor.size(); i++)
            {
                temp_vector_bottom_floor_for_sorting.push_back(2); // Bottom floor
                temp_vector_bottom_floor_for_sorting.push_back(temp_vector_bottom_floor[i]);
                tot_comp_positions_temp.push_back(temp_vector_bottom_floor_for_sorting);
                temp_vector_bottom_floor_for_sorting.clear();
            }

            tot_comp_positions = tot_comp_positions_temp;

            // Build up to print truck
            for(int i = 0; i != tot_comp_positions.size(); i++)
            {
                if(tot_comp_positions[i][0]==1) // Top floor
                {
                    for(int j = count_occu1; j != truck_size/2 + 1; j++)
                    {    
                        if(tot_comp_positions[i][1] == j)
                        {                            
                            temp1 += compartment_top;
                            temp2 += space_delimiter_occupied;
                            temp3 += compartment_bottom;
                            count_occu1 = j+1;
                            count_occu_top += 1;
                            break;
                        }
                        else
                        {
                            temp1 += compartment_top;
                            temp2 += space_delimiter;
                            temp3 += compartment_bottom;
                            count_occu_top += 1;
                        }
                    }    
                }
                if(tot_comp_positions[i][0]==2) // Bottom floor
                {
                    for(int j = count_occu2; j != truck_size/2 + 1; j++)
                    {
                        if(tot_comp_positions[i][1] == j)
                        {
                            temp4 += compartment_top;
                            temp5 += space_delimiter_occupied;
                            temp6 += compartment_bottom;
                            count_occu2 = j + 1;
                            count_occu_bottom += 1;
                            break;
                        }
                        else
                        {
                            temp4 += compartment_top;
                            temp5 += space_delimiter;
                            temp6 += compartment_bottom;
                            count_occu_bottom += 1;
                        }   
                    }
                }
            }

            // This adds empty compartments
            for(int i = 0; i != truck_size/2 - count_occu_top; i++)
            {

                temp1 += compartment_top;
                temp2 += space_delimiter;
                temp3 += compartment_bottom; 
            }

            for(int i = 0; i != truck_size/2 - count_occu_bottom; i++)
            {

                temp4 += compartment_top;
                temp5 += space_delimiter;
                temp6 += compartment_bottom; 
            }
            cout << "       " << " Truck number: " << truck_no << endl;
            cout << cab_top << temp1<< endl;
            cout << cab_middle1 << temp2 << endl;
            cout << cab_middle2 << temp3 << endl;
            cout << cab_bottom1 << temp4 << endl;
            cout << cab_bottom2 << temp5 << endl; 
            cout << cab_width << temp6 << endl;
        }

        void Truck::load_car(int pos_y, int pos_x, Car car)
        {
            
            allowed_weight = max_load - car.weight;
            if(allowed_weight < 0)
            {
                cout << "Max load has been reached" << endl;
            }
            else
            {
                std::vector<int> comp_position;
                comp_position.push_back(pos_y);
                comp_position.push_back(pos_x);
                tot_comp_positions.push_back(comp_position);
                car.y_position = pos_y;
                car.x_position = pos_x;
                car.location.city_name = location_truck;
                loaded_cars.push_back(car);

            }
        }
        void Truck::unload_car(Car &car)
        {
            int tot_comp_positions_size;
            car.location.city_name = location_truck;
            allowed_weight += car.weight;
            tot_comp_positions_size = tot_comp_positions.size();
            if(tot_comp_positions_size == 0)
            {
                cout << "No loaded cars on truck nr " << truck_no << endl;
            }
            else if(tot_comp_positions_size > 1)
            {
                for(int i = 0; i != tot_comp_positions_size; i++)
                {
                    if(car.y_position == tot_comp_positions[i][0] && car.x_position == tot_comp_positions[i][1])
                    {
                        tot_comp_positions.erase(tot_comp_positions.begin()+i);  
                    }
                }
                for(int i = 0; i != loaded_cars.size(); i++)
                {
                    if(loaded_cars[i].reg_no == car.reg_no)
                    {
                        loaded_cars.erase(loaded_cars.begin()+i);
                    }
                }
            }
            else
            {
                tot_comp_positions.clear();
                loaded_cars.clear();
            }
            
        }
        void Truck::send_truck(Map destination)
        {
            truck_origin = location_truck;
            truck_destination = destination.city_name;
            location_truck = destination.city_name;

            for(int i = 0; i != loaded_cars.size(); i++)
            {
                loaded_cars[i].location.city_name= destination.city_name;
            }
        }
        void Truck::print_loaded_cars()
        {   
            if(tot_comp_positions.size() > 0 )
            {
                cout << "      " << " Truck number: " << truck_no 
                << " | Truck destination: " << location_truck << endl;
                for(int i = 0; i != loaded_cars.size() ; i++)
                {
                    cout << "       " << loaded_cars[i].reg_no <<  " | "  << loaded_cars[i].destination.city_name<< " | row:"<< loaded_cars[i].y_position
                    << " col:"<<loaded_cars[i].x_position <<endl;
                }
            }
            else
            {
                cout << "No cars on truck no " << truck_no << endl;
            }
            
        }

        void Truck::load_optimal_order(std::vector<Map> best_path, std::vector<Car> cars_to_be_sent) //BYT TILL BEST_PATH
        {

            int count = 0;
            Car car_test = cars_to_be_sent[0];
            
            for(int i = best_path.size()-1; i != 0 ; i--)
            {
                for(int j = 0; cars_to_be_sent.size() != j; j++)
                {
                    if(cars_to_be_sent[j].destination.city_name == best_path[i].city_name)
                    {
                        count++;
                        if(count < truck_size/2 + 1)
                        {
                            load_car(1, count, cars_to_be_sent[j]);
                        }
                        else if(count > truck_size/2 && count < truck_size + 1)
                        {
                            load_car(2, count - truck_size/2, cars_to_be_sent[j]);
                        }   
                    }

                }

            }

        }
        std::vector<Map> Truck::get_cities_for_ACO(std::vector<Car> cars_collection, Map truck_origin, Map truck_destination)
        {
            std::vector<Map> cities_for_ACO;
            std::vector<std::string> cities_for_ACO_string;  
            std::vector<std::string> cars_collection_dest;

            
            for(int i = 0; cars_collection.size() != i; i++)
            {
                cars_collection_dest.push_back(cars_collection[i].destination.city_name);
            }

            cities_for_ACO_string.push_back(truck_destination.city_name);
            cities_for_ACO.push_back(truck_origin);
            cities_for_ACO_string.push_back(truck_origin.city_name);

            for(int i = 0; cars_collection_dest.size() != i; i++)
            {
                if(std::find(cities_for_ACO_string.begin(), cities_for_ACO_string.end(), cars_collection_dest[i]) == cities_for_ACO_string.end())
                {
                    cities_for_ACO.push_back(cars_collection[i].destination);
                    cities_for_ACO_string.push_back(cars_collection[i].destination.city_name);
                }   
            }
            cout << "size " << cities_for_ACO.size() << endl;
            for(int i = 0; cities_for_ACO.size() != i; i++)
            {
                cities_for_ACO[i].idx = i;
            }
            return cities_for_ACO;
        }
