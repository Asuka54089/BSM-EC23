

#include "../include/bsm_basic.h"

using namespace std;

BsmBasic::BsmBasic() {}

void BsmBasic::init(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers, bool is_rotated, vector<int> &male_opt_matching, vector<int> &female_opt_matching, vector<Rotation> &rotations, vector<pair<int, int>> &rotation_edges)
{

    antichain_counter = 0;
    smi.init(male_prefers, female_prefers);

    if (is_rotated == false)
    {
        // generate opt matching & rotations
        /***************/
        smi.init(male_opt_matching, female_opt_matching, rotations);
        smg.init(rotation_edges, rotations.size(), rotations.back().depth);
    }
    else
    {
        smi.init(male_opt_matching, female_opt_matching, rotations);
        smg.init(rotation_edges, rotations.size(), rotations.back().depth);
    }
}

void BsmBasic::init_method() {}

void BsmBasic::init_result() {
    opt_marriage = smi.male_opt;
    
    antichain_counter = 0;
    male_worse_counter = 0;
    female_worse_counter = 0;
}

bool BsmBasic::update_result(Marriage &x, set<int> S)
{
    Counter(x);

    int x_score = x.pos[x.worst_case];
    int best_score = opt_marriage.pos[opt_marriage.worst_case];

    if (x_score < best_score)
    {
        opt_marriage = x;
        opt_S = S;
        return true;
    }
    return false;
}

void BsmBasic::Counter(Marriage &x){
    antichain_counter++;
    if(x.worst_case==0){
       male_worse_counter++;
    }
    else female_worse_counter++;
}

void BsmBasic::find_bsm() {}

void BsmBasic::package_results(const string &results_file, double runtime){};
