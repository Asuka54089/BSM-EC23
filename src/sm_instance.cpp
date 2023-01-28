#include "../include/sm_instance.h"

using namespace std;

SmInstance::SmInstance() {}

void SmInstance::init(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers)
{
    this->male_prefers = male_prefers;
    this->female_prefers = female_prefers;
    init_positions(male_prefers, female_prefers);
}

void SmInstance::init(vector<int> &male_opt_matching, vector<int> &female_opt_matching, vector<Rotation> &rotations)
{
    init_opt_matchings(male_opt_matching,female_opt_matching);
    init_rotations(rotations);
}

void SmInstance::init_positions(vector<vector<int>> &male_prefers, vector<vector<int>> &female_prefers)
{
    int size = male_prefers.size();
    for (int i = 0; i < size; i++)
    {
        vector<int> tmp(size, -1);
        male_positions.push_back(tmp);
        female_positions.push_back(tmp);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            male_positions[i][male_prefers[i][j]] = j;
            female_positions[i][female_prefers[i][j]] = j;
        }
    }
}


void SmInstance::init_opt_matchings(vector<int> &male_opt_matching, vector<int> &female_opt_matching)
{
    init_matching(male_opt_matching,male_opt); 
    init_matching(female_opt_matching,female_opt); 
}

void SmInstance::init_matching(vector<int> &matching,Marriage &x){
    x.init(matching);

    int m=-1;
    int w= -1;
    for(int i=0;i<matching.size();i++){
        m = i;
        w = matching[i];
        x.pos[0] = x.pos[0] + get_index_w_in_m(m,w);
        x.pos[1] = x.pos[1]+ get_index_m_in_w(w,m);
    }
    if(x.pos[0]>=x.pos[1]){
        x.worst_case = 0;
    }
    else{
        x.worst_case = 1;
    }
}

// void SmOperation::init_rotations(vector<Rotation> &rotations){
//     this->rotations = rotations;
// }
void SmInstance::init_rotations(vector<Rotation> &rotations)
{
    Rotation elim_r;
    int m = -1;
    int w1 = -1;
    int w2 = -1;

    int m_pos = 0;
    int w_pos = 0;
    int m_pos_elim = 0;
    int w_pos_elim = 0;

    for (Rotation r : rotations)
    {

        m_pos = 0;
        w_pos = 0;
        m_pos_elim = 0;
        w_pos_elim = 0;

        elim_r.clear();
        vector<int> next_females;
        r.get_next_females(next_females);
        for (int i = 0; i < r.size(); i++)
        {
            m = r.Rm[i];
            w1 = r.Rw[i];
            w2 = next_females[i];
            elim_r.insert(m, w2);

            m_pos = m_pos + get_index_w_in_m(m, w1);
            w_pos = w_pos + get_index_m_in_w(w1, m);
            m_pos_elim = m_pos_elim + get_index_w_in_m(m, w2);
            w_pos_elim = w_pos_elim + get_index_m_in_w(w2, m);
        }

        elim_r.weight = r.weight;
        elim_r.depth = r.depth;
        elim_rotations.push_back(elim_r);

        elim_r.male_position_weight = m_pos - m_pos_elim;
        elim_r.female_position_weight = w_pos - w_pos_elim;
    }
}

void SmInstance::list_rotation_layers(){
    vector<int> layer;
    for(int r=0;r<elim_rotations.size();r++){
        if(elim_rotations[r].depth>rotation_layers.size()){
            rotation_layers.push_back(layer);
            layer.clear();
        }
        layer.push_back(r);
    }
    rotation_layers.push_back(layer);
}

vector<int> SmInstance::closedsubset_to_matching(set<int> &subset)
{
    // int step = 0;
    vector<int> matching = male_opt.male_to_female;
    int m = -1;
    int w = -1;
    for (int r : subset)
    {
        //cout<<"replace"<<r<<"-"<<elim_rotations[r].size()<<endl;
        for (int i = 0; i < elim_rotations[r].size(); i++)
        {
            m = elim_rotations[r].Rm[i];
            w = elim_rotations[r].Rw[i];
            matching[m] = w;
            // step++;
        }
    }
    // cout<<"step"<<step<<endl;
    return matching;
}

int SmInstance::get_index_w_in_m(int m, int w)
{
    return male_positions[m][w];
}
int SmInstance::get_index_m_in_w(int w, int m)
{
    return female_positions[w][m];
}
int SmInstance::get_w_by_index(int m, int i)
{
    return male_prefers[m][i];
}
int SmInstance::get_m_by_index(int w, int i)
{
    return female_prefers[w][i];
}

// int SmInstance::calculate_esm_score(vector<int> &matching){
//     int w_score = 0;
//     int m_score = 0;
//     int w = 0;
//     for(int m=0;m<matching.size();m++)
//     {
//         w = matching[m];
//         // the female position that male can get
//         m_score = m_score + male_positions[m][w];
//         w_score = w_score + female_positions[w][m];
//     }
//     return m_score + w_score;
// }

// int SmInstance::calculate_diff_S(set<int> &subset){
//     int diff_S = 0;
//     int r = -1;

//     for(int r:subset)
//     {
//         diff_S = diff_S + eliminated_rotations[r].weight;
//     }
//     return diff_S;
// }
