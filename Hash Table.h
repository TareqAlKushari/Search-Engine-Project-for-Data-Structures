#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <list>
using namespace std;

// A class template for hash table nodes
template <class K, class V>
class HashNode {
    public:
        K key; // The key stored in the node
        V value; // The value stored in the node

        // A constructor that creates a node with a given key and value
        HashNode(K k, V v) {
            key = k;
            value = v;
        }
};

// A class template for hash tables using separate chaining
template <class K, class V>
class HashTable {
    private:
        int capacity; // The maximum number of buckets in the table
        int size; // The current number of nodes in the table
        vector<list<HashNode<K,V>>> table; // The vector of lists to store the nodes

        // A helper method that returns the hash value of a given key
        int hashFunction(K key) const {
            return key % capacity; // Use the modulo operator as a simple hash function
        }

    public:
        // A constructor that creates a hash table with a given capacity and no nodes
        HashTable(int c) {
            capacity = c;
            size = 0;
            table.resize(c); // Resize the vector of lists to have c lists, one for each bucket
        }

        // A method that returns the current number of nodes in the table
        int getSize() const {
            return size;
        }

        // A method that checks if the table is empty or not
        bool isEmpty() const {
            return size == 0;
        }

        // A method that inserts a new node with a given key and value into the table, or updates the value if the key already exists
        void insert(K key, V value) {
            int index = hashFunction(key); // Get the hash value of the key and store it as the index of the bucket
            for (auto& node : table[index]) { // Loop through the nodes in the bucket
                if (node.key == key) { // Check if the key of the current node matches the given key
                    node.value = value; // Update the value of the current node with the given value
                    return; // Return from the method
                }
            }
            // If the loop ends without finding a matching key, create a new node with the given key and value and add it to the front of the bucket
            table[index].push_front(HashNode<K,V>(key, value));
            size++; // Increment the size by one
        }

        // A method that removes a node with a given key from the table, throwing an exception if it does not exist
        void remove(K key) {
            int index = hashFunction(key); // Get the hash value of the key and store it as the index of the bucket
            for (auto it = table[index].begin(); it != table[index].end(); it++) { // Loop through the nodes in the bucket using an iterator 
                if (it->key == key) { // Check if the key of the current node matches the given key 
                    table[index].erase(it); // Erase the current node from the bucket 
                    size--; // Decrement the size by one 
                    return; // Return from the method 
                }
            }
            // If the loop ends without finding a matching key, throw an exception 
            throw logic_error("Key not found");
        }

        // A method that searches for a given key in the table and returns its value, throwing an exception if it does not exist
        V search(K key) const {
            int index = hashFunction(key); // Get the hash value of the key and store it as the index of the bucket
            for (auto& node : table[index]) { // Loop through the nodes in the bucket
                if (node.key == key) { // Check if the key of the current node matches the given key
                    return node.value; // Return the value of the current node
                }
            }
            // If the loop ends without finding a matching key, throw an exception
            throw logic_error("Key not found");
        }

        // A method to search for a value in the hash table and return its key
        K searchByValue(V value) {
            for (int i = 0; i < capacity; i++) { // loop through each index in the vector
                for (auto& pair : table[i]) { // loop through each list in the vector
                    if (pair.second == value) { // if the value is found, return its key
                        return pair.first;
                    }
                }
            }
            throw out_of_range("Value not found"); // if the value is not found, throw an exception
        }

        // A method that prints all keys and values in the table
        void print() const {
            for (int i = 0; i < capacity; i++) { // Loop through all buckets in the table
                cout << i << ": "; // Print the current bucket index
                for (auto& node : table[i]) { // Loop through the nodes in the current bucket
                    cout << "(" << node.key << ", " << node.value << ") "; // Print each key and value pair 
                }
                cout << endl;
            }
        }

        vector<int> get_time_taken(vector<V> api, vector<V> data) {
            vector<int> time_for_ds;
            for(auto method : api) {
                auto start = chrono::high_resolution_clock::now();

                if(method == "insert()") {
                    for(size_t i = 0; i < data.size(); i++){
                        insert(i, data.at(i));
                    }
                }
                else if(method == "delete()") {
                    for(size_t i = (data.size()/2); i < data.size(); i++){
                        remove(i);
                        insert(i, data.at(i));
                    }
                    
                }
                else if(method == "search()") {
                    search(50);
                }
                else if(method == "size()") {
                    int x = getSize();
                }
                else if(method == "sort()") {
                    for(size_t i = 0; i < data.size(); i++){
                        remove(i);
                        insert(i, data.at(i));
                    }
                }
                auto stop = chrono::high_resolution_clock::now();

                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

                time_for_ds.push_back(duration.count());
            }
            return time_for_ds;
        }
};
