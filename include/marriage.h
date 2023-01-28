#ifndef MARRIAGE_H_
#define MARRIAGE_H_

//#include "../include/structs.h"

#include <iostream>
#include <vector>
using namespace std;


class Marriage
{
public:
	vector<int> male_to_female;
	//vector<int> female_to_male;
	
	// equality cost
	int egalitarian_cost;
	int sex_equal_cost;

	int pos[2]; // sum P_m(w), sum P_w(m)
	int worst_case; //-1:default 0:male 1:female

	Marriage();
	
	void init(vector<int> &male_to_female);
	void clear();



};



#endif