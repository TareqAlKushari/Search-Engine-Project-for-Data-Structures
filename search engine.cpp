#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include <DynamicArray>
using namespace std;

// A function that takes an API as input and returns a list of data structures that can support it
vector<string> get_possible_data_structures(string api) {
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
    if (api.find("random access") != string::npos) {
        random_access = true;
    }
    if (api.find("sorting") != string::npos) {
        sorting = true;
    }
    if (api.find("insertion") != string::npos || api.find("deletion") != string::npos) {
        insertion_deletion = true;
    }
    if (api.find("ordered") != string::npos) {
        ordered_data = true;
    }

  // Filter out the data structures that are not suitable for the API
  // This is a simplified example, you may need to use more sophisticated filtering techniques
    if (!random_access && !sorting && !insertion_deletion && !ordered_data) {
        // No specific requirement, any data structure can be used
        result.push_back("array");
        result.push_back("vector");
        result.push_back("linked list");
        result.push_back("tree");
        result.push_back("hash table");
    } else if (random_access && !sorting && !insertion_deletion && !ordered_data) {
        // Only random access required, array, vector, and hash table can be used
        result.push_back("array");
        result.push_back("vector");
        result.push_back("hash table");
    } else if (!random_access && sorting && !insertion_deletion && !ordered_data) {
        // Only sorting required, linked list and tree can be used
        result.push_back("linked list");
        result.push_back("tree");
    } else if (!random_access && !sorting && insertion_deletion && !ordered_data) {
        // Only insertion or deletion required, linked list and hash table can be used
        result.push_back("linked list");
        result.push_back("hash table");
    } else if (!random_access && !sorting && !insertion_deletion && ordered_data) {
        // Only ordered data required, array, vector, linked list, and tree can be used
        result.push_back("array");
        result.push_back("vector");
        result.push_back("linked list");
        result.push_back("tree");
    } else if (random_access && sorting && !insertion_deletion && !ordered_data) {
        // Random access and sorting required, array and vector can be used
        result.push_back("array");
        result.push_back("vector");
    } else if (random_access && !sorting && insertion_deletion && !ordered_data) {
        // Random access and insertion or deletion required, vector and hash table can be used
        result.push_back("vector");
        result.push_back("hash table");
    } else if (random_access && !sorting && !insertion_deletion && ordered_data) {
        // Random access and ordered data required, array and vector can be used
        result.push_back("array");
        result.push_back("vector");
    } else if (!random_access && sorting && insertion_deletion && !ordered_data) {
        // Sorting and insertion or deletion required, linked list and tree can be used
        result.push_back(“linked list”); result.push_back(“tree”); 
    } else if (!random_access && sorting && !insertion_deletion && ordered_data) { 
        // Sorting and ordered data required, linked list and tree can be used 
        result.push_back(“linked list”); result.push_back(“tree”); 
    } else if (!random_access && !sorting && insertion_deletion && ordered_data) { 
        // Insertion or deletion and ordered data required, linked list and tree can be used 
        result.push_back(“linked list”); result.push_back(“tree”); 
    } else if (random_access && sorting && insertion_deletion && !ordered_data) { 
        // Random access, sorting, and insertion or deletion required, no suitable data structure exists 
        result.clear(); 
    } else if (random_access && sorting && !insertion_deletion && ordered_data) { 
        // Random access, sorting, and ordered data required, array and vector can be used 
        result.push_back(“array”); result.push_back(“vector”); 
    } else if (random_access && !sorting && insertion_deletion && ordered_data) { 
        // Random access, insertion or deletion, and ordered data required, no suitable data structure exists 
        result.clear(); 
    }

    // Rank the data structures based on their advantages and disadvantages for the API 
    // This is a simplified example, you may need to use more sophisticated ranking techniques

    // Define a helper function that compares two data structures based on some criteria 
    bool compare(string ds1,string ds2,string api){ 
        // For example: prefer vectors over arrays for frequent resizing, 
        // prefer hash tables over other data structures for fast search, 
        // prefer arrays over other data structures for minimal memory usage, 
        // prefer trees over other data structures for balanced structure

        if(api.find(“resizing”)!=string::npos) { 
            if(ds1==“vector”&&ds2==“array”) { 
                return true; 
            } else if(ds1==“array”&&ds2==“vector”) { 
                return false; 
            } 
        }

        if(api.find(“search”)!=string::npos) { 
            if(ds1==“hash table”&&ds2!=“hash table”) { 
                return true; 
            } else if(ds1!=“hash table”&&ds2==“hash table”) { 
                return false; 
            } 
        }

        if(api.find(“memory”)!=string::npos) { 
            if(ds1==“array”&&ds2!=“array”) { 
                return true; 
            } else if(ds1 != “array” && ds2 ==“array”) { 
                return false; 
            } 
        }

        if(api.find(“balanced”)!=string::npos) { 
            if(ds1==“tree”&&ds2!=“tree”) { 
                return true; 
            } else if(ds1!=“tree”&&ds2==“tree”) { 
                return false; 
            } 
        }

        // If none of the criteria applies, return false by 
        default (no preference) 
        return false; 
    }

    // Sort the vector of possible data structures using the helper function 
    sort(result.begin(),result.end(),[&](string ds1,string ds2) { return compare(ds1,ds2,api); });

    // Return the vector of possible data structures 
    return result; 
}


vector<vector<int>> get_time_taken(vector<string> data_structures, vector<string> api) {
    vector<vector<int>> time_taken;

    for(auto ds : data_structures) {
        vector<int> time_for_ds;

        for(auto method : api) {
            auto start = chrono::high_resolution_clock::now();

            if(ds == "array") {
                DynamicArray array;
                if(method == "add(string s)") {
                    array.append("hello");
                }
                else if(method == "remove()") {
                    array.remove("hello");
                }
                else if(method == "contains()") {
                    array.contains("hello");
                }
                else if(method == "size()") {
                    array.size();
                }
                else if(method == "print()") {
                    array.print();
                }
            }
            else if(ds == "linked list") {
                LinkedList list;
                if(method == "add(string s)") {
                    list.append("hello");
                }
                else if(method == "remove()") {
                    list.remove("hello");
                }
                else if(method == "contains()") {
                    list.contains("hello");
                }
                else if(method == "size()") {
                    list.size();
                }
                else if(method == "print()") {
                    list.print();
                }
            }
            else if(ds == "BST") {
                BST tree;
                if(method == "add(string s)") {
                    tree.append("hello");
                }
                else if(method == "remove()") {
                    tree.remove("hello");
                }
                else if(method == "contains()") {
                    tree.contains("hello");
                }
                else if(method == "size()") {
                    tree.size();
                }
                else if(method == "print()") {
                    tree.print();
                }
            }
            else if(ds == "hash table") {
                HashTable table;
                if(method == "add(string s)") {
                    table.append("hello");
                }
                else if(method == "remove()") {
                    table.remove("hello");
                }
                else if(method == "contains()") {
                    table.contains("hello");
                }
                else if(method == "size()") {
                    table.size();
                }
                else if(method == "print()") {
                    table.print();
                }
            }

            auto stop = chrono::high_resolution_clock::now();

            auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

            time_for_ds.push_back(duration.count());
        }

        time_taken.push_back(time_for_ds);
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
    //vector<string> api = {"insert(int x)", "delete(int x)", "search(int x)", "sort()", "size()"};
    vector<string> api = {"add(string s)", "remove()", "contains()", "size()", "print()"};

    vector<string> data_structures = get_possible_data_structures(api);

    vector<vector<int>> time_taken = get_time_taken(data_structures, api);
}