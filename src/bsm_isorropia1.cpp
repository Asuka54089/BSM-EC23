
#include "../include/bsm_isorropia1.h"

using namespace std;

void BsmIsorropia1::init_method()
{
    smg.init_pred_and_succ();

    
    flag_jump_r_related_calculation = false;
    flag_disadvantage_rotations.resize(smg.rotation_num);

}

void BsmIsorropia1::init_result()
{
    opt_marriage = smi.male_opt;

    antichain_counter = 0;
    male_worse_counter = 0;
    female_worse_counter = 0;

    A1_counter = 0;
    A2_counter = 0;
    A3_counter = 0;
}

void BsmIsorropia1::find_bsm()
{
    init_method();
    init_result();

    // update flag_check_opt_matchings
    if (check_opt_matchings())
    {
        return;
    }

    calculate_r_related_marraiges();
    collect_candidate_rotations();

    local_search_right();
    local_search_left();
}

bool BsmIsorropia1::check_opt_matchings()
{
    if (smi.male_opt.pos[0] > smi.male_opt.pos[1])
    {
        opt_marriage = smi.male_opt;
        flag_check_opt_matchings = 1;
        return true;
    }
    if (smi.female_opt.pos[1] > smi.female_opt.pos[0])
    {
        opt_marriage = smi.female_opt;
        flag_check_opt_matchings = 2;
        return true;
    }
    flag_check_opt_matchings = 0;
    return false;
}

void BsmIsorropia1::calculate_r_related_marraiges()
{
    // set<int> tmp_A;
    // set<int> tmp_S;
    // vector<int> tmp_matching;
    // Marriage tmp_x;

    for (int r = 0; r < smg.rotation_num; r++)
    {
        // calculate first
        flag_jump_r_related_calculation = false;
        // check parent of r
        for(int parent:smg.parents[r]){
            //cout<<flag_disadvantage_rotations[parent]<<endl;
            if(flag_disadvantage_rotations[parent] == true){
                male_disadvantage_rotations.push_back(r);
                flag_disadvantage_rotations[r] = true;
                flag_jump_r_related_calculation = true;
                break;
            }
        }

        if(flag_jump_r_related_calculation==true){
            continue;
        }

        

        tmp_A.clear();
        tmp_A.insert(r);
        tmp_S = smg.antichain_to_closedsubset(tmp_A);
        tmp_matching = smi.closedsubset_to_matching(tmp_S);
        smi.init_matching(tmp_matching, tmp_x);
        r_related_marraiges.push_back(tmp_x);
        if (tmp_x.worst_case == 0)
        {
            male_disadvantage_rotations.push_back(r);
            flag_disadvantage_rotations[r] = true;
        }
        else
        {
            female_disadvantage_rotations.push_back(r);
        }
    }
}

void BsmIsorropia1::collect_candidate_rotations()
{
    // collect right candidate rotations
    //vector<int> r_intersection;
    for (auto itr : male_disadvantage_rotations)
    {
        tmp_r_intersection = set_intersect(smg.parents[itr], male_disadvantage_rotations);
        if (tmp_r_intersection.size() == 0)
        {
            right_candidate_rotations.push_back(itr);
        }
    }

    // collect left candidate rotations
    // set<int> tmp_A;
    // set<int> tmp_S;
    // vector<int> tmp_matching;
    // Marriage tmp_x;

    smi.list_rotation_layers();

    for (int d = 0; d < smg.max_depth; d++)
    {
        tmp_A = vector_to_set(smi.rotation_layers[d]);
        tmp_S = smg.antichain_to_closedsubset(tmp_A);
        tmp_matching = smi.closedsubset_to_matching(tmp_S);
        smi.init_matching(tmp_matching, tmp_x);
        if (tmp_x.worst_case == 0)
        {
            max_female_disadvantage_layer = d - 1;
            break;
        }
    }

    for (auto itr : female_disadvantage_rotations)
    {
        if (smi.elim_rotations[itr].depth > max_female_disadvantage_layer)
        {
            left_candidate_rotations.push_back(itr);
        }
    }
}

void BsmIsorropia1::local_search_right()
{
    for (auto itr : right_candidate_rotations)
    {
        A1_counter++;
        set<int> S;
        S.insert(itr);
        update_result(r_related_marraiges[itr],S);
    }
}

void BsmIsorropia1::local_search_left()
{
    // set<int> tmp_A;
    // set<int> tmp_S;
    // vector<int> tmp_matching;
    // Marriage tmp_x;

    if (max_female_disadvantage_layer >= 0)
    {
        tmp_A = vector_to_set(smi.rotation_layers[max_female_disadvantage_layer]);
        tmp_S = smg.antichain_to_closedsubset(tmp_A);
        tmp_matching = smi.closedsubset_to_matching(tmp_S);
        smi.init_matching(tmp_matching, tmp_x);
        update_result(tmp_x,tmp_S);
        CounterA1A2(tmp_x);
    }

    vector<int> D_out;
    deque<int> R0;
    tmp_A = vector_to_set(left_candidate_rotations);
    set<int> S_left = smg.antichain_to_closedsubset(tmp_A);
    set<int> removed_S;
    init_R0(D_out, R0, S_left);

    enumerate(D_out, R0, S_left, removed_S);
}

void BsmIsorropia1::update_subgraph_S_left(set<int> &S_left)
{
    vector<int> S_left_vector = set_to_vector(S_left);

    for (int r = 0; r < smg.rotation_num; r++)
    {
        tmp_r_intersection = set_intersect(smg.parents[r], S_left_vector);
        S_left_parents.push_back(tmp_r_intersection);

        tmp_r_intersection = set_intersect(smg.children[r], S_left_vector);
        S_left_children.push_back(tmp_r_intersection);
    }

    vector<int> full_S;
    for (int r = 0; r < smg.rotation_num; r++)
    {
        full_S.push_back(r);
    }

    vector<int> del_rotations = set_diff(full_S, S_left_vector);

    for (int r : del_rotations)
    {
        S_left_children[r].clear();
        S_left_children[r].push_back(-1);
        S_left_parents[r].clear();
        S_left_parents[r].push_back(-1);
    }
}

void BsmIsorropia1::init_R0(vector<int> &D_out, deque<int> &R0, set<int> &S_left)
{
    update_subgraph_S_left(S_left);

    int out_degree = 0;
    for (auto r : S_left)
    {
        out_degree = S_left_children[r].size();
        if (S_left_children[r].size() == 1 && *S_left_children[r].begin() == -1)
        {
            D_out.push_back(nINF); // r not in S_left
        }
        else
        {
            D_out.push_back(out_degree);
        }

        if (out_degree == 0)
        {
            R0.push_back(r);
        }
    }
}

void BsmIsorropia1::enumerate(vector<int> &D_out, deque<int> &R0, set<int> &S, set<int> &removed_S)
{
    // if (antichain_counter > MAX_ANTICHAIN_NUM)
    // {
    //     return;
    // }

    Marriage x;
    vector<int> matching;

    if (!R0.empty())
    {
        // check Antichain in A1 and A2
        //vector<int> r_intersection;
        tmp_r_intersection.clear();
        set_intersection(removed_S.begin(), removed_S.end(),
                         left_candidate_rotations.begin(), left_candidate_rotations.end(),
                         back_inserter(tmp_r_intersection));
        if (tmp_r_intersection.size() == left_candidate_rotations.size())
        {
            // cout<<"range"<<endl;
            return;
        }

        int r = R0.front();
        // cout<<"r-: "<<r<<endl;
        R0.pop_front();
        S.erase(r);
        removed_S.insert(r);

        matching = smi.closedsubset_to_matching(S);
        smi.init_matching(matching, x);
        flag_update = update_result(x,S);
        CounterA1A2(x);

        // early stop
        // jump over branch(i)
        if (flag_update == true && x.worst_case == 1)
        {
            cout << "stop" << endl;
            S.insert(r);
            removed_S.erase(r);
            enumerate(D_out, R0, S, removed_S);
            R0.push_front(r);
            return;
        }

        for (int next_r : S_left_parents[r])
        {
            D_out[next_r] = D_out[next_r] - 1;
            if (D_out[next_r] == 0)
            {
                R0.push_back(next_r);
            }
        }
        enumerate(D_out, R0, S, removed_S);
        for (int next_r : S_left_parents[r])
        {
            D_out[next_r] = D_out[next_r] + 1;
            if (D_out[next_r] == 1)
            {
                R0.pop_back();
            }
        }

        S.insert(r);
        removed_S.erase(r);
        // cout<<"r+: "<<r<<endl;
        enumerate(D_out, R0, S, removed_S);
        R0.push_front(r);
    }
}

void BsmIsorropia1::CounterA1A2(Marriage &x)
{
    if (x.worst_case == 0)
    {
        A2_counter++;
    }
    else
        A3_counter++;
    ;
}

void BsmIsorropia1::package_results(const string &instance_dir, double runtime)
{
    // for(int r: opt_S){
    //     cout<<r<<" ";
    // }
    // cout<<endl;
    map<string, int> counters = {
        {"antichain_counter", antichain_counter},
        {"male_worse_counter", male_worse_counter},
        {"female_worse_counter", female_worse_counter},
        {"Rmale_size", male_disadvantage_rotations.size()},
        {"Rfemale_size", female_disadvantage_rotations.size()},
        {"Rright_size", right_candidate_rotations.size()},
        {"Rleft_size", left_candidate_rotations.size()},
        {"l_max", max_female_disadvantage_layer},
        {"A1_counter", A1_counter},
        {"A2_counter", A2_counter},
        {"A3_counter", A3_counter},
    };
    map<string, string> info = {};
    string save_path = instance_dir + "_m2";
    save_results(save_path, "isorropia1", runtime, counters, info, opt_marriage);
}
