
#include "../include/bsm_enum_reverse.h"

using namespace std;

void BsmEnumReverse::init_result()
{
    opt_marriage = smi.female_opt;

    antichain_counter = 0;
    male_worse_counter = 0;
    female_worse_counter = 0;
}

void BsmEnumReverse::find_bsm()
{
    init_result();
    
    vector<int> D_out;
    deque<int> R0;

    init_R0(D_out, R0);

    set<int> full_S;
    for(int r=0; r< smg.rotation_num;r++){
        full_S.insert(r);
    }
    
    // the first result: female optimal stable marriage (S is R)
    update_result(opt_marriage,full_S);

    enumerate(D_out, R0, full_S);
}

void BsmEnumReverse::init_R0(vector<int> &D_out, deque<int> &R0)
{
    int out_degree = 0;
    for (int i = 0; i < smg.rotation_num; i++)
    {
        out_degree = smg.children[i].size();
        D_out.push_back(out_degree);
        if (out_degree == 0)
        {
            R0.push_back(i);
        }
    }
}

// The Stable Marriage Problem: Structure and Algorithms (P125)
// Efficent Enumeration of All Stable Matchings
void BsmEnumReverse::enumerate(vector<int> &D_out, deque<int> &R0, set<int> &S)
{
    if (antichain_counter > MAX_ANTICHAIN_NUM)
    {
        return;
    }

    Marriage x;
    vector<int> matching;

    if (!R0.empty())
    {
        int r = R0.front();
        // cout<<"r-: "<<r<<endl;
        R0.pop_front();
        S.erase(r);

        matching = smi.closedsubset_to_matching(S);
        smi.init_matching(matching, x);
        update_result(x,S);

        for (int next_r : smg.parents[r])
        {
            D_out[next_r] = D_out[next_r] - 1;
            if (D_out[next_r] == 0)
            {
                R0.push_back(next_r);
            }
        }
        enumerate(D_out, R0, S);
        for (int next_r : smg.parents[r])
        {
            D_out[next_r] = D_out[next_r] + 1;
            if (D_out[next_r] == 1)
            {
                R0.pop_back();
            }
        }

        S.insert(r);
        // cout<<"r+: "<<r<<endl;
        enumerate(D_out, R0, S);
        R0.push_front(r);
    }
}

void BsmEnumReverse::package_results(const string &instance_dir, double runtime)
{
    map<string, int> counters = {
        {"antichain_counter", antichain_counter},
        {"male_worse_counter", male_worse_counter},
        {"female_worse_counter", female_worse_counter},
    };
    map<string, string> info = {};
    string save_path = instance_dir + "_m1";
    save_results(save_path, "enum_reverse", runtime, counters, info, opt_marriage);
}
