#ifndef ACO_H
#define ACO_H
#include "map.h"
#include <vector>

using std::vector;

void print_square_matrix(vector<vector<double> > matrix);

double calculate_distance(Map city1, Map city2);

double get_nearest_neighbour_path_length(vector<Map> city_location);

vector<vector<double> > initialize_pheromone_matrix(double tao0, int no_cities);

vector<vector<double> > initialize_delta_matrix(int no_cities);

double get_sum_tabu_list(vector<Map> &visited_cities, vector<Map> cities,
int current_city_idx, vector<vector<double> > &tao_matrix, double alpha, double beta);

vector<Map> get_unvisited_cities(vector<Map> &cities, vector<Map> visited_cities); //&

vector<Map> build_path(vector<vector<double> > tao_matrix, vector<Map> cities); //&

double calculate_path_distance(vector<Map> tot_path, Map final_dest);

vector<vector<double> > update_tao_for_ant(double path_length,vector<vector<double> > delta_tao_matrix,
 vector<Map> tot_path, vector<Map> cities);

vector<vector<double> > vaporize(vector<vector<double> > tao_matrix, vector<vector<double> > delta_tao, double evap_rate);
#endif