#ifndef BSM_ENUM_REVERSE_H_
#define BSM_ENUM_REVERSE_H_

#include "bsm_basic.h"

class BsmEnumReverse : public BsmBasic
{
public:
    void init_result();

    BsmEnumReverse() : BsmBasic(){};

    void find_bsm();

    void init_R0(vector<int> &D_out, deque<int> &R0);

    void enumerate(vector<int> &D_out, deque<int> &R0, set<int> &S);

    void package_results(const string &instance_dir, double runtime);
};

#endif