#ifndef SM_BASIC_H_
#define SM_BASIC_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <math.h>
#include <numeric>
#include <time.h>

#include "utils.h"
#include "structure.h"
#include "sm_instance.h"
#include "sm_graph.h"

class BsmBasic
{
public:
    // Static Variables
    const int MAX_ANTICHAIN_NUM = 1000000;

    /* Input a SM instance */
    BsmBasic();
    // Stable Marraige Instance Object
    SmInstance smi;
    // Rotation Graph Object
    SmGraph smg;
    // Init smg and smo
    void init(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers, bool is_rotated, vector<int> &male_opt_matching, vector<int> &female_opt_matching, vector<Rotation> &rotations, vector<pair<int, int>> &rotation_edges);

    /* Init */
    // init for different methods
    void init_method(); // @override
    // init to update the best result
    void init_result(); // @override

    /* Result */
    // update the best result
    bool update_result(Marriage &x, set<int> S); // @override
    Marriage opt_marriage;
    set<int> opt_S;

    /* Methods */
    void find_bsm(); // @override

    /* Counters */
    void Counter(Marriage &x); // @override
    int antichain_counter; //# enumerated antichains
    int male_worse_counter;
    int female_worse_counter;

    /* Save */
    void package_results(const string &instance_dir, double runtime); // @override
};

#endif