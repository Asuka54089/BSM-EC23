#include "../include/sm_graph.h"

using namespace std;

SmGraph::SmGraph() {}

void SmGraph::init(vector<pair<int, int>> &rotation_edges, int rotation_num, int max_depth)
{
    // init rotation graph
    this->rotation_num = rotation_num;
    this->max_depth = max_depth;

    //init children & parents
    children.resize(rotation_num);
    parents.resize(rotation_num);
    for (auto edge : rotation_edges)
    {
        int rs = edge.first;
        int rt = edge.second;

        children[rs].push_back(rt);
        parents[rt].push_back(rs);
    }
}

void SmGraph::init_pred_and_succ()
{
    pred.resize(rotation_num);
    //succ.resize(rotation_num);
    for (int i = 0; i < rotation_num; i++)
    {
        for (auto j : children[i])
        {
            pred[j].insert(i);
            //succ[i].push_back(j);
            for (auto k : pred[i])
            {
                pred[j].insert(k);
                //succ[k].push_back(j);
            }
        }
    }
}

set<int> SmGraph::antichain_to_closedsubset(set<int> antichain)
{
    set<int> closed_subset;
    for (int r : antichain)
    {
        closed_subset.insert(r);
        closed_subset.insert(pred[r].begin(), pred[r].end());
    }
    return closed_subset;
}

