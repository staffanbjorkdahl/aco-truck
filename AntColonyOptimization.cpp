#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <random>
#include "map.h"

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::find;
using namespace std;




void print_square_matrix(vector<vector<double> > matrix)
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
}

double calculate_distance(Map city1, Map city2)
{
    double x_diff;
    double y_diff;
    x_diff = city1.x_coordinate-city2.x_coordinate;
    y_diff = city1.y_coordinate-city2.y_coordinate;
    return sqrt(x_diff*x_diff+y_diff*y_diff);
}

double get_nearest_neighbour_path_length(vector<Map> city_location)
{
    double dist;
    double dist_sum = 0;
    double best_dist;
    double return_sum;
    vector<string> visited_cities_temp;
    visited_cities_temp.push_back(city_location[0].city_name);
    int temp_visitied_city_idx;
    int visited_city_idx = 0;

    for(int i = 0; i != city_location.size()-1; i++)
    {
        double dist_check = numeric_limits<double>::max();
        for(int j = 0; j != city_location.size() ;j++)
        {
            double dist = calculate_distance(city_location[visited_city_idx],city_location[j]);
            bool city_not_visited = find(visited_cities_temp.begin(),visited_cities_temp.end(),city_location[j].city_name)
             == visited_cities_temp.end();

            if(dist < dist_check && city_not_visited && i != j)
            {
                dist_check = dist;
                temp_visitied_city_idx = j;
                dist_sum += dist_check;

            }
        }
        visited_city_idx = temp_visitied_city_idx;
        visited_cities_temp.push_back(city_location[visited_city_idx].city_name);
        return_sum = dist_sum;
    }
    return return_sum;
    
}

vector<vector<double> > initialize_pheromone_matrix(double tao0, int no_cities)
{
    vector<vector<double> > tao_matrix;
    vector<double> tao_matrix_row;
    for(int i = 0; no_cities != i; i++)
    {
        for(int j = 0; no_cities != j; j++)
        {
            tao_matrix_row.push_back(tao0);
        }
        tao_matrix.push_back(tao_matrix_row);
    }
    return tao_matrix;
}

vector<vector<double> > initialize_delta_matrix(int no_cities)
{
    vector<vector<double> > delta_tao_matrix;
    vector<double> delta_tao_matrix_row;
    for(int i = 0; no_cities != i; i++)
    {
        for(int j = 0; no_cities != j; j++)
        {
            delta_tao_matrix_row.push_back(0);
        }
        delta_tao_matrix.push_back(delta_tao_matrix_row);
    }
    return delta_tao_matrix;
}
double get_sum_tabu_list(vector<Map> visited_cities, vector<Map> cities,
int current_city_idx, vector<vector<double> > tao_matrix, double alpha, double beta)
{
    double sum_pheromone = 0.0;
    double sum_denom = 0.0;
    double temp_tao = 0.0;
    double temp_dist = 0.0;
    double denom_pre_summation = 0.0;
    
    vector<string> unvisited_cities_names;
    vector<string> visited_city_names;
    vector<string> cities_names;
    vector<int> unvisited_idx;

    for(int i = 0; visited_cities.size() != i; i++)
    {
        visited_city_names.push_back(visited_cities[i].city_name);
    }

    for(int i = 0; cities.size() != i; i++)
    {
        if (find(visited_city_names.begin(), visited_city_names.end(), cities[i].city_name) == visited_city_names.end())
        {
            unvisited_cities_names.push_back(cities[i].city_name);
            unvisited_idx.push_back(i);
        }

    }

    for(int i = 0; unvisited_idx.size() != i; i++)
    {
        //cout << current_city_idx << " " << unvisited_idx[i] << endl;
        //cout << "-----unvis-" << endl;
        temp_tao = tao_matrix[unvisited_idx[i]][current_city_idx];
        //cout << "temptao " << temp_tao << endl;
        temp_dist = calculate_distance(cities[current_city_idx],cities[unvisited_idx[i]]);
        denom_pre_summation = pow(temp_tao,alpha)*pow(1/temp_dist,beta);
        //denom_pre_summation = pow(1/temp_dist,beta);
        sum_pheromone += denom_pre_summation;
        /*if(unvisited_idx.size() == 1)
        {
            cout << "sumphero" << sum_pheromone<< endl;
        }*/

        
    }
    
    return sum_pheromone;
}

vector<Map> get_unvisited_cities(vector<Map> &cities, vector<Map> visited_cities)
{
    vector<string> visited_city_names;
    vector<Map> unvisited_cities;
    vector<int> unvisited_idx;

    for(int i = 0; visited_cities.size() != i; i++)
    {
        visited_city_names.push_back(visited_cities[i].city_name);
    }

    for(int i = 0; cities.size() != i; i++)
    {
        if(find(visited_city_names.begin(), visited_city_names.end(), cities[i].city_name) == visited_city_names.end())
        {
            unvisited_cities.push_back(cities[i]);
            unvisited_idx.push_back(i);
        }

    }
    return unvisited_cities;
}

vector<Map> build_path(vector<vector<double> > tao_matrix, vector<Map> cities)
{
    int city_counter = 0;
    int current_city_idx = 0;
    int next_city_idx = 1;
    int picked_city_idx;
    double alpha = 1.0;
    double beta = 2;
    double sum_prob = 0;
    double init_decision_prob;
    double decision_prob;
    double prob_path;
    double denominator;
    double numerator;
    double distance_between_nodes;
    double tao;
    vector<int> visited_cities_idx;
    vector<Map> visited_cities;
    vector<Map> unvisited_cities;
    
    visited_cities.push_back(cities[current_city_idx]);
    visited_cities_idx.push_back(current_city_idx);
    unvisited_cities = get_unvisited_cities(cities, visited_cities);

    while(city_counter < cities.size()-1)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);
        init_decision_prob = dis(gen);
        while(sum_prob <= init_decision_prob && next_city_idx <= cities.size())
        {
            if(next_city_idx != current_city_idx && next_city_idx < cities.size()
            && find(visited_cities_idx.begin(), visited_cities_idx.end(), next_city_idx) == visited_cities_idx.end())
            {
                distance_between_nodes = calculate_distance(cities[current_city_idx],cities[next_city_idx]);
                denominator = get_sum_tabu_list(visited_cities,cities,current_city_idx,tao_matrix,alpha,beta);
                tao = tao_matrix[next_city_idx][current_city_idx];
                numerator = pow(tao,alpha)*pow(1/distance_between_nodes,beta);
                //numerator = pow(1/distance_between_nodes,beta);
                //cout << "nummmmmmmm" << numerator << endl;
                prob_path = numerator/denominator;
                
                //cout << "rpo " << tao << endl;
                //cout << current_city_idx << " " << next_city_idx << endl;
                //print_square_matrix(tao_matrix);
                
                //cout <<"sum "<< sum_prob<< endl;
                if(prob_path > 1)
                {
                    cout << "----------prob_pat > 1-------------" <<endl;
                    cout << "probpahth " << prob_path << endl;
                    cout << "tao " << tao << endl;
                    cout << "numerator "<< numerator << endl;
                    cout << "denom " << denominator << endl;
                    
                    cout << current_city_idx << " " << next_city_idx << endl;
                    cout << "IIII------------------IIII" << endl;
                }
                sum_prob += prob_path;
                picked_city_idx = next_city_idx;
                next_city_idx++;
            }
            else
            {
                next_city_idx++;
            }

            
        }
        //cout << "p i " << picked_city_idx << endl;
        visited_cities.push_back(cities[picked_city_idx]);
        visited_cities_idx.push_back(picked_city_idx);
        current_city_idx = picked_city_idx;
        city_counter++;
        next_city_idx = 0;
        sum_prob = 0;
    }
    return visited_cities;
}

double calculate_path_distance(vector<Map> tot_path, Map final_dest)
{
    double tot_distance = 0;
    tot_path.push_back(final_dest);
    for(int i = 0; tot_path.size()-1 != i; i++)
    {
        tot_distance += calculate_distance(tot_path[i],tot_path[i+1]);
    }
    //cout <<"totttt " << tot_distance << endl; 
    return tot_distance;
}

vector<vector<double> > update_tao_for_ant(double path_length,vector<vector<double> > delta_tao_matrix,
 vector<Map> tot_path, vector<Map> cities)
{
    //vector<vector<double> > delta_tao;

    
    //cout << "delta_tao size " << delta_tao_matrix.size() << endl;
    //cout << "tot_path size " << tot_path.size() << endl;  
    for(int i = 0; tot_path.size()-1 != i; i++)
    {
        //cout << tot_path[i].idx << " " << tot_path[i+1].idx << endl;
        //cout << i<< " ij " << i+1 << endl;
        delta_tao_matrix[tot_path[i].idx][tot_path[i+1].idx] += 1/path_length;
    }
    //cout << path_length << endl;
    //print_square_matrix(delta_tao_matrix);
    return delta_tao_matrix;
}

vector<vector<double> > vaporize(vector<vector<double> > tao_matrix, vector<vector<double> > delta_tao, double evap_rate)
{
    vector<vector<double> > temp_tao_matrix = tao_matrix;
    for(int i = 0; tao_matrix.size() != i; i++)
    {
        for(int j = 0; tao_matrix.size() != j; j++)
        {
            tao_matrix[i][j] = (1-evap_rate)*temp_tao_matrix[i][j] + delta_tao[i][j];
        }
    }
    return tao_matrix;
}