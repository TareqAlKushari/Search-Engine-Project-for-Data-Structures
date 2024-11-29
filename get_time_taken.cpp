#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

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