#ifndef ROTATION_H_
#define ROTATION_H_

#include <iostream>
#include <vector>
using namespace std;


class Rotation
{
public:
	vector<int> Rw;
	vector<int> Rm;

	int depth;
	int weight;
	int size();

	int male_position_weight;
	int female_position_weight;

	Rotation();
	//~Rotation(void);

	void insert(int m, int w);
	// get next females after rotation elimination
	void get_next_females(vector<int> &next_Rw);

	void clear();
};



#endif