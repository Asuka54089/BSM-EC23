#ifndef SM_INSTANCE_H_
#define SM_INSTANCE_H_

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
// mac OS
//#include "../lib/stdc++.h"
// ubuntu
//#include <bits/stdc++.h>

#include "rotation.h"
#include "marriage.h"
#include "structure.h"
using namespace std;

// Stable Marraige Operation Class
// variables of stable marriage instance
// operations on matchings and closed subsets
class SmInstance
{
public:
    
    SmInstance();

    // init preferences
    void init(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers);

    void init_positions(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers);
    vector<vector<int>> male_positions,female_positions;

    int get_index_w_in_m(int w,int m);
    int get_index_m_in_w(int w,int m);
    int get_w_by_index(int m, int i);
    int get_m_by_index(int w, int i);

    // init opt matchings & rotations
    void init(vector<int> &male_opt_matching,vector<int> &female_opt_matching,vector<Rotation> &rotations);
    vector<vector<int>> male_prefers,female_prefers;

    void init_opt_matchings(vector<int> &male_opt_matching,vector<int> &female_opt_matching);
    void init_matching(vector<int> &matching, Marriage &x);
    Marriage male_opt;
    Marriage female_opt;
    
    // store rotation pairs after elimination transformation (for directly opt-sm/S-->sm)
    void init_rotations(vector<Rotation> &rotations);
    vector<Rotation> elim_rotations;
    
    //in local search
    void list_rotation_layers();
    vector<vector<int>> rotation_layers;
    
    
    // closed subset --> stable marriage (opt-sm/S-->sm, by rotation elimination)
    vector<int> closedsubset_to_matching(set<int> &subset);

    /* Calculation */ 
    // sum by rotation weights
    int calculate_diff_S(set<int> &subset); 

};

#endif
