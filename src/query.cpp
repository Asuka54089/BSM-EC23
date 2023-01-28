// query

#include "../include/query.h"

using namespace std;

Query::Query(string instance_dir)
{
    // load sm instance
    load_preferences(instance_dir, male_prefers, female_prefers);
    load_matchings(instance_dir + "_m", male_opt_matching, female_opt_matching);
    load_rotations(instance_dir + "_r", rotations);
    load_rotation_edges(instance_dir + "_e", rotation_edges);

    //init result file
    this->instance_dir = instance_dir;
}

void Query::test()
{
    cout << "test start" << endl;
    cout << "test end" << endl;
}


void Query::run(int method){
    switch (method)
    {
    case 0:
        cout<< "m0:enum    start" << endl;
        bsm_enum();
        cout<< "m0:enum    done" << endl;
        break;
    case 1:
        cout<< "m1:enum_reverse    start" << endl;
        bsm_enum_reverse();
        cout<< "m1:enum_reverse    done" << endl;
        break;
    case 2:
        cout<< "m2:isorropia    start" << endl;
        bsm_isorropia1();
        cout<< "m2:isorropia    start" << endl;
        break;
    case 3:
        cout<< "m2:isorropia    start" << endl;
        bsm_isorropia2();
        cout<< "m2:isorropia    start" << endl;
        break;
    default:
        break;
    }
}

void Query::bsm_enum()
{
    BsmEnum x = BsmEnum();

    x.init(male_prefers, female_prefers, true, male_opt_matching, female_opt_matching, rotations, rotation_edges);

    start_time = clock();
    x.find_bsm();
    end_time = clock();

    runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    x.package_results(instance_dir, runtime);
}

void Query::bsm_enum_reverse()
{
    BsmEnumReverse x = BsmEnumReverse();

    x.init(male_prefers, female_prefers, true, male_opt_matching, female_opt_matching, rotations, rotation_edges);

    start_time = clock();
    x.find_bsm();
    end_time = clock();

    runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    x.package_results(instance_dir, runtime);
}


void Query::bsm_isorropia1()
{
    BsmIsorropia1 x = BsmIsorropia1();

    x.init(male_prefers, female_prefers, true, male_opt_matching, female_opt_matching, rotations, rotation_edges);

    start_time = clock();
    x.find_bsm();
    end_time = clock();

    runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    x.package_results(instance_dir, runtime);
}

void Query::bsm_isorropia2()
{
    BsmIsorropia2 x = BsmIsorropia2();

    x.init(male_prefers, female_prefers, true, male_opt_matching, female_opt_matching, rotations, rotation_edges);

    start_time = clock();
    x.find_bsm();
    end_time = clock();

    runtime = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    x.package_results(instance_dir, runtime);
}
