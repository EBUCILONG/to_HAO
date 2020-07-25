//
// Created by Oruqimaru on 18/7/2020.
//

#include "avl_tree.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>


using namespace std;

int main(int argc, char *argv[]){

    int test_scale = atoi(argv[1]);

    vector<int> inputs;
    AvlTree<int> T;
//    map<int, int> M;

    for(int i = 0; i < test_scale; i++){
        inputs.push_back(i);
    }

    random_shuffle(inputs.begin(),inputs.end());

    clock_t startTime,endTime;

    startTime = clock();
    for(int i = 0; i < test_scale; i++){
        T.Insert(inputs[i]);
    }
    endTime = clock();
    cout << "My Avl Tree Use: " <<(endTime - startTime) *1.0 / CLOCKS_PER_SEC << "s" << endl;

 //   startTime = clock();
 //   for(int i = 0; i < test_scale; i++){
 //       M.insert(pair<int, int>(inputs[i], inputs[i]));
 //   }
 //   endTime = clock();
 //   cout << "STL Map Use: " <<(endTime - startTime) *1.0 / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}
