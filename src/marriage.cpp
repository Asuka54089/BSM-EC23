#include "../include/marriage.h"

using namespace std;

Marriage::Marriage(){}


void Marriage::init(vector<int> &male_to_female)
{
    clear();
    this->male_to_female = male_to_female;

    // does not use
    // female_to_male.resize(male_to_female.size(),-1);
    // int w = -1;
    // int m = -1;
    // for(int i=0;i<male_to_female.size();i++){
    //     m = i;
    //     w = male_to_female[i];
    //     female_to_male[w] = m; 
    // }
}

void Marriage::clear(){
    egalitarian_cost = 0; 
    sex_equal_cost= 0;

    pos[0] = 0;
	pos[1] = 0;
	worst_case = -1;

    male_to_female.clear();
    //female_to_male.clear();
}



