#ifndef BSM_ENUM_H_
#define BSM_ENUM_H_

#include "bsm_basic.h"

class BsmEnum : public BsmBasic
{
public:

    BsmEnum() : BsmBasic(){};

    void find_bsm();

    void init_R0(vector<int> &D_in, deque<int> &R0);

    void enumerate(vector<int> &D_in, deque<int> &R0, set<int> &S);

    void package_results(const string &instance_dir, double runtime);
};

#endif