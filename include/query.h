#ifndef QUERY_H_
#define QUERY_H_

#include <utility>
#include <vector>

#include "../include/utils.h"
#include "../include/rotation.h"

#include "../include/bsm_basic.h"

#include "../include/bsm_enum.h"
#include "../include/bsm_enum_reverse.h"
#include "../include/bsm_isorropia1.h"
#include "../include/bsm_isorropia2.h"



class Query
{
public:

    // input instance
    vector<vector<int>> male_prefers;
    vector<vector<int>> female_prefers;
    vector<int> male_opt_matching,female_opt_matching;
    vector<pair<int, int>> rotation_edges;
    vector<Rotation> rotations;

    string instance_dir;

    clock_t start_time, end_time;
    double runtime;


    Query(string instance_dir);


    void run(int method);
    
    
    void bsm_enum();
    void bsm_enum_reverse();
    
    void bsm_isorropia1();
    void bsm_isorropia2();
        

    void test();
   

};

#endif
