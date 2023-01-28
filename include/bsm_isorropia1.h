#ifndef BSM_ISORROPIA1_H_
#define BSM_ISORROPIA1_H_

#include "bsm_basic.h"


class BsmIsorropia1 : public BsmBasic
{
public:
    void init_method();
    void init_result();

    BsmIsorropia1() : BsmBasic(){};

    void find_bsm();

    bool check_opt_matchings();

    void calculate_r_related_marraiges();
    vector<Marriage> r_related_marraiges;
    vector<int> male_disadvantage_rotations;
    vector<int> female_disadvantage_rotations;
    vector<bool> flag_disadvantage_rotations; // 0: female-worse 1:male-worse
    bool flag_jump_r_related_calculation;
    
    void collect_candidate_rotations();
    int max_female_disadvantage_layer;
    vector<int> right_candidate_rotations;
    vector<int> left_candidate_rotations;

    void local_search_right();
    void local_search_left();


    // ENUM-
    vector<vector<int>> S_left_children;
    vector<vector<int>> S_left_parents;
    void update_subgraph_S_left(set<int> &S_left);
    void init_R0(vector<int> &D_out, deque<int> &R0, set<int> &S_left);
    void enumerate(vector<int> &D_out, deque<int> &R0, set<int> &S, set<int> &removed_S);

    // flag
    int flag_check_opt_matchings; // [-1]: default; [0]:general case; [1]:return male-optimal sm; [2]:return female-optimal sm

    // early stop
    bool flag_update; // last update 

    void CounterA1A2(Marriage &x);
    int A1_counter;
    int A2_counter;
    int A3_counter;


    void package_results(const string &instance_dir, double runtime);


    // temporary variables
    set<int> tmp_A;
    set<int> tmp_S;
    vector<int> tmp_matching;
    Marriage tmp_x;
    vector<int> tmp_r_intersection;
};

#endif