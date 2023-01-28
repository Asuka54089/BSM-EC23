#include "../include/query.h"
#include "../include/lib/Format.h"

// #include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
    if (argc != 3)
        {
            printf("Wrong arguments");
            return 0;
        }

        string key = argv[1];

        int method = 0;
        sscanf(argv[2], "%d", &method);


        string dir_format = "./instance/{}/{}";
            
        string instance_dir = util::Format(dir_format, key, key);

        Query x = Query(instance_dir);
        x.run(method);
  

}



// for an instance
// int main(int argc, char *argv[])
// {

    // Dataset Key (foler name)
    // [Input Files] 
    // 1. preference lists    key
    // 2. rotation graph (node)  key_r
    // 3. rotation graph (edge)  key_e
    // 4. male-optimal/female-optimal matching  key_m
    // 5. instance info (n, type, rotation graph, hard instance params) 

    // string key = "n8";
    // string key = "uniform";
    // string key = "gaussian";

    // string key = "hard_256_1";
    
    // string dir_format = "./instance/{}/{}";
    
    // string instance_dir = util::Format(dir_format, key, key);
    
    // Query x = Query(instance_dir);

    // x.bsm_enum();
    // x.bsm_enum_reverse();
    // x.bsm_isorropia1();

// }


// for functions
// int main(int argc, char *argv[])
// {

//     vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8};
//     vector<int> v2{5, 9, 7, 10};
    
//     vector<int> x = set_intersect(v1,v2);
//     cout<<"test"<<endl;


// }
