#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "map.h"



        Map::Map(double x_coordinate, double y_coordinate, std::string city_name, int idx)
        {
            this->x_coordinate = x_coordinate;
            this->y_coordinate = y_coordinate;
            this->city_name = city_name;
            this->idx = idx;
        }
        int Map::find_max_idx(std::vector<Map> cities)
        {
            std::vector<int> idx_vector;
            for(int i = 0; cities.size() != i; i++)
            {
                idx_vector.push_back(cities[i].idx);
            }
            int max = *std::max_element(idx_vector.begin(), idx_vector.end());
            std::cout <<"Max value: "<<max<< std::endl;
            return max;
        }
              