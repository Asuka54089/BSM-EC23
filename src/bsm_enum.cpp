
#include "../include/bsm_enum.h"

using namespace std;



// EnumS
void BsmEnum::find_bsm()
{
    init_result();

    vector<int> D_in;
    deque<int> R0;

    init_R0(D_in, R0);

    set<int> null_S;
    // the first result: male optimal stable marriage (S is empty)
    update_result(opt_marriage,null_S);

    enumerate(D_in, R0, null_S);

}

void BsmEnum::init_R0(vector<int> &D_in, deque<int> &R0)
{
    int in_degree = 0;
    for (int i = 0; i < smg.rotation_num; i++)
    {
        in_degree = smg.parents[i].size();
        D_in.push_back(in_degree);
        if (in_degree == 0)
        {
            R0.push_back(i);
        }
    }
}

// The Stable Marriage Problem: Structure and Algorithms (P125)
// Efficent Enumeration of All Stable Matchings
void BsmEnum::enumerate(vector<int> &D_in, deque<int> &R0, set<int> &S)
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
        S.insert(r);

        matching = smi.closedsubset_to_matching(S);

        smi.init_matching(matching, x);
        bool y = update_result(x,S);


        for (int next_r : smg.children[r])
        {
            D_in[next_r] = D_in[next_r] - 1;
            if (D_in[next_r] == 0)
            {
                R0.push_back(next_r);
            }
        }
        enumerate(D_in, R0, S);
        for (int next_r : smg.children[r])
        {
            D_in[next_r] = D_in[next_r] + 1;
            if (D_in[next_r] == 1)
            {
                R0.pop_back();
            }
        }

        S.erase(r);
        // cout<<"r+: "<<r<<endl;
        enumerate(D_in, R0, S);
        R0.push_front(r);
    }
}

void BsmEnum::package_results(const string &instance_dir, double runtime)
{   
    // cout<<"xxxx"<<endl;
    // for(int r: opt_S){
    //     cout<<r<<" ";
    // }
    // cout<<endl;
    map<string, int> counters = {
        {"antichain_counter", antichain_counter},
        {"male_worse_counter", male_worse_counter},
        {"female_worse_counter", female_worse_counter},
    };
    map<string, string> info = {};
    string save_path = instance_dir + "_m0";
    save_results(save_path, "enum", runtime, counters, info, opt_marriage);
}
