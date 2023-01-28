#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "limits.h"

//ubuntu
#include <experimental/filesystem>
//mac
//#include <filesystem>

#include "../include/rotation.h"
#include "../include/marriage.h"
#include "../include/structure.h"
// #include "../include/sm_operation.h"

using namespace std;
//ubuntu
namespace fs = std::experimental::filesystem;
//mac OS
//namespace fs = std::filesystem;

const int MAX_ANTICHAIN_NUM = 100000000;
// int pINF = INT_MAX;
const int nINF = INT_MIN;


void load_preferences(const string &dir, vector<vector<int>> &male_prefers,vector<vector<int>> &female_prefers);


void load_matchings(const string &dir, vector<int> &matching1,vector<int> &matching2);

void load_rotations(const string &rotation_dir, vector<Rotation> &rotations);
void load_rotation_edges(const string &rotation_dir, vector<pair<int, int>> &rotation_edges);


vector<int> set_intersect(vector<int> &A, vector<int> &B);
vector<int> set_diff(vector<int> &A, vector<int> &B);
set<int> vector_to_set(vector<int> &A);
vector<int> set_to_vector(set<int> &A);


/* save results */
bool save_results(const string &results_file, string method, double time, map<string, int> &counters, map<string, string> &lists, Marriage &result);
string convert_list(const vector<int> info);

/* Print */
void print_adj(vector<set<int>> &adj, string type);
void print_matching(vector<int> &matching, string title);
void print_rotation_set(set<int> &rotation_set, string title);


#endif