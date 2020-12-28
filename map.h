#ifndef MAP_H
#define MAP_H
#include <string>
#include <vector>

class Map
{
    public:
        double x_coordinate;
        double y_coordinate;
        std::string city_name;
        int idx;
        Map(double x_coordinate, double y_coordinate, std::string city_name, int idx);
        Map(){};
        int find_max_idx(std::vector<Map> cities);
              
};
#endif