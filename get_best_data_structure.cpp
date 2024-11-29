#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

string get_best_data_structure(vector<string> data_structure, vector<vector<int>> time_taken, vector<string> api) {
    string best_data_structure;

    int min_avg_time = INT_MAX;

    for(int i = 0; i < data_structure.size(); i++) {
        string ds = data_structure[i];
        vector<int> tt = time_taken[i];

        int avg_time = accumulate(tt.begin(), tt.end(), 0) / tt.size();

        if(avg_time <= min_avg_time) {
            best_data_structure = ds;
            min_avg_time = avg_time;
        }
    }

    return best_data_structure;
}