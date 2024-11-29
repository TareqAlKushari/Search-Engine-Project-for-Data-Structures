#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include "Main.h"
#include "ToArray.h"
#include "Stack.h"
#include "Queue.h"
#include "LinkedList.h"
#include "Hash Table.h"
#include "BST.h"

using namespace std;

vector<string> get_possible_data_structures(vector<string> api) {
        // A vector to store the possible data structures
        vector<string> result;

        // A flag to indicate if the API requires random access
        bool random_access = false;

        // A flag to indicate if the API requires sorting
        bool sorting = false;

        // A flag to indicate if the API requires insertion or deletion at any position
        bool insertion_deletion = false;

        // A flag to indicate if the API requires ordered data
        bool ordered_data = false;

        // Parse the API string and set the flags accordingly
        // This is a simplified example, you may need to use more sophisticated parsing techniques

        for(auto method : api) {
            if (method == "random access") {
                random_access = true;
            }
            if (method == "sorting") {
                sorting = true;
            }
            if (method == "insertion" || method == "deletion") {
                insertion_deletion = true;
            }
            if (method == "ordered") {
                ordered_data = true;
            }
        }


        if (!random_access && !sorting && !insertion_deletion && !ordered_data) {
            // No specific requirement, any data structure can be used
            result.push_back("array");
            result.push_back("stack");
            result.push_back("queue");
            result.push_back("linked list");
            result.push_back("tree");
            result.push_back("hash table");
            result.push_back("graphs");
        } else if (random_access && !sorting && !insertion_deletion && !ordered_data) {
            // Only random access required, array, vector, and hash table can be used
            result.push_back("array");
            result.push_back("hash table");
        } else if (!random_access && sorting && !insertion_deletion && !ordered_data) {
            // Only sorting required, linked list and tree can be used
            result.push_back("linked list");
            result.push_back("tree");
        } else if (!random_access && !sorting && insertion_deletion && !ordered_data) {
            // Only insertion or deletion required, linked list and hash table can be used
            result.push_back("stack");
            result.push_back("queue");
            result.push_back("linked list");
            result.push_back("hash table");
        } else if (!random_access && !sorting && !insertion_deletion && ordered_data) {
            // Only ordered data required, array, vector, linked list, and tree can be used
            result.push_back("array");
            result.push_back("stack");
            result.push_back("queue");
            result.push_back("linked list");
            result.push_back("tree");
        } else if (random_access && sorting && !insertion_deletion && !ordered_data) {
            // Random access and sorting required, array and vector can be used
            result.push_back("array");
        } else if (random_access && !sorting && insertion_deletion && !ordered_data) {
            // Random access and insertion or deletion required, vector and hash table can be used
            result.push_back("hash table");
        } else if (random_access && !sorting && !insertion_deletion && ordered_data) {
            // Random access and ordered data required, array and vector can be used
            result.push_back("array");
        } else if (!random_access && sorting && insertion_deletion && !ordered_data) {
            // Sorting and insertion or deletion required, linked list and tree can be used
            result.push_back("linked list"); 
            result.push_back("tree"); 
        } else if (!random_access && sorting && !insertion_deletion && ordered_data) { 
            // Sorting and ordered data required, linked list and tree can be used 
            result.push_back("linked list"); 
            result.push_back("tree"); 
        } else if (!random_access && !sorting && insertion_deletion && ordered_data) { 
            // Insertion or deletion and ordered data required, linked list and tree can be used 
            result.push_back("linked list"); 
            result.push_back("tree"); 
        } else if (random_access && sorting && insertion_deletion && !ordered_data) { 
            // Random access, sorting, and insertion or deletion required, no suitable data structure exists 
            result.clear(); 
        } else if (random_access && sorting && !insertion_deletion && ordered_data) { 
            // Random access, sorting, and ordered data required, array and vector can be used 
            result.push_back("array"); 
        } else if (random_access && !sorting && insertion_deletion && ordered_data) { 
            // Random access, insertion or deletion, and ordered data required, no suitable data structure exists 
            result.clear(); 
        }

        // Return the vector of possible data structures 
        return result; 
    }

// template <class T>
vector<vector<int>> get_full_time_taken(vector<string> data_structures, vector<string> api, vector<string> data) {
    vector<vector<int>> time_taken;

    for(auto ds : data_structures) {
        if(ds == "array"){
            ToArray<std::string> arr;
            time_taken.push_back(arr.get_time_taken(api, data));
        }
        else if(ds == "stack"){
            Stack<string> st;
            time_taken.push_back(st.get_time_taken(api, data));
        }
        else if(ds == "queue") {
            DynamicQueue<string> qu;
            time_taken.push_back(qu.get_time_taken(api, data));
        }
        else if(ds == "linked list") {
            LinkedList<string> linked;
            time_taken.push_back(linked.get_time_taken(api, data));
        }
        else if(ds == "hash table") {
            HashNode<int, string> node(10, "rew");
            HashTable<int, string> ht(5);
            time_taken.push_back(ht.get_time_taken(api, data));
        }
        else if(ds == "BST") {
            BST<string> tree;
            time_taken.push_back(tree.get_time_taken(api, data));
        }
    }
    return time_taken;
}

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

int main() {
    int i = 0;
    std::cout << "Define an API that requires fast insert(), delete(), search(), size(), and sort() operations. " << endl;

    vector<string> api = {"insert()", "delete()", "search()", "size()", "sort()"};
    vector<string> data_structure = {"array", "stack", "queue", "linked list", "hash table", "BST"};

    
    vector<string> data;
    int size_data;
    std::cout << "What is the size of data: " << endl;
    std::cin >> size_data;
    for(size_t i = 0; i < size_data; i++) {
        data.push_back("i");
    }

    vector<vector<int>> time_taken = get_full_time_taken(data_structure, api, data);
    string bset = get_best_data_structure(data_structure, time_taken, api);
    for(vector<int> time : time_taken){
        std::cout << "[" ;
        for(int t : time) {
            std::cout << t << " ";
        }
        std::cout << "]" << " time taken by " << data_structure.at(i) <<  " for each method" << endl;
        i++;
    }
    std::cout << endl;

    std::cout << "The best data structure is : " << bset << endl;

}