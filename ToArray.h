#include <iostream>
#include <vector>
#include <chrono>
using namespace std;


// A class template for dynamic arrays using vector
template <class T> 
class ToArray {
    private:
        vector<T> data; // The underlying vector to store the elements
        int size; // The current number of elements in the array
        int capacity; // The maximum number of elements the array can hold

    public:
        // A default constructor that creates an empty array
        ToArray() {
            size = 0;
            capacity = 10;
            data.resize(capacity); // Allocate memory for the vector
        }

        // A parameterized constructor that creates an array with a given size and fills it with a default value
        ToArray(int n, T val) {
            size = n;
            capacity = n;
            data.resize(capacity); // Allocate memory for the vector
            for (int i = 0; i < size; i++) {
                data[i] = val; // Assign the default value to each element
            }
        }

        // A copy constructor that creates a deep copy of another array
        ToArray(const ToArray<T>& other) {
            size = other.size;
            capacity = other.capacity;
            data.resize(capacity); // Allocate memory for the vector
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i]; // Copy each element from the other array
            }
        }

        // A destructor that frees the memory allocated by the vector
        ~ToArray() {
            data.clear(); // Clear the vector
        }

        // An assignment operator that assigns the contents of another array to this array
        ToArray<T>& operator=(const ToArray<T>& other) {
            if (this != &other) { // Avoid self-assignment
                size = other.size;
                capacity = other.capacity;
                data.resize(capacity); // Allocate memory for the vector
                for (int i = 0; i < size; i++) {
                    data[i] = other.data[i]; // Copy each element from the other array
                }
            }
            return *this; // Return a reference to this array
        }

        // An index operator that returns a reference to the element at a given position
        T& operator[](int index) {
            if (index >= 0 && index < size) { // Check if the index is valid
                return data[index]; // Return a reference to the element at that index
            }
            else { // Throw an exception if the index is out of bounds
                throw out_of_range("Index out of bounds");
            }
        }

        // A const index operator that returns a const reference to the element at a given position
        const T& operator[](int index) const {
            if (index >= 0 && index < size) { // Check if the index is valid
                return data[index]; // Return a const reference to the element at that index
            }
            else { // Throw an exception if the index is out of bounds
                throw out_of_range("Index out of bounds");
            }
        }

        // A method that returns the current number of elements in the array
        int getSize() const {
            return size;
        }

        // A method that returns the maximum number of elements the array can hold
        int getCapacity() const {
            return capacity;
        }

        // A method that checks if the array is empty or not
        bool isEmpty() const {
            return size == 0;
        }

        // A method that adds a new element at the end of the array, resizing it if necessary
        void append(T val) {
            if (size == capacity) { // Check if the array is full
                capacity *= 2; // Double the capacity
                data.resize(capacity); // Resize the vector accordingly
            }
            data[size] = val; // Assign the new value to the last position
            size++; // Increment the size by one
        }

        // A method that inserts a new element at a given position, shifting the existing elements to the right, resizing it if necessary
        void insert(int index, T val) {
            if (index >= 0 && index <= size) { // Check if the index is valid
                if (size == capacity) { // Check if the array is full
                    capacity *= 2; // Double the capacity
                    data.resize(capacity); // Resize the vector accordingly
                }
                for (int i = size - 1; i >= index; i--) { 
                    data[i + 1] = data[i]; // Shift each element one position to the right from the given index onwards 
                }
                data[index] = val; // Assign the new value to the given position 
                size++; // Increment the size by one 
            }
            else { // Throw an exception if the index is out of bounds 
                throw out_of_range("Index out of bounds");
            }
        }

        // A method that removes an element at a given position, shifting the existing elements to the left 
        void remove(int index) {
            if (index >= 0 && index < size) { // Check if the index is valid 
                for (int i = index + 1; i < size; i++) { 
                    data[i - 1] = data[i]; // Shift each element one position to the left from the given index onwards 
                }
                size--; // Decrement the size by one 
            }
            else { // Throw an exception if the index is out of bounds 
                throw out_of_range("Index out of bounds");
            }
        }

        // A method to search for an element in the array using linear search
        int search(T element) {
            for (int i = 0; i < size; i++) { // loop through the array from 0 to size - 1
                if (data[i] == element) { // if the current element is equal to the target element, return its index
                    return i;
                }
            }
            return -1; // if the element is not found, return -1
        }

        // A method to sort the array elements in ascending order using bubble sort
        void sort() {
            for (int i = 0; i < size - 1; i++) { // loop through the array from 0 to size - 2
                for (int j = 0; j < size - i - 1; j++) { // loop through the array from 0 to size - i - 2
                    if (data[j] > data[j+1]) { // if the current element is greater than the next element, swap them
                        T temp = data[j];
                        data[j] = data[j+1];
                        data[j+1] = temp;
                    }
                }
            }
        }

        // A method that prints all the elements in the array 
        void print() const {
            cout << "[";
            for (int i = 0; i < size; i++) {
                cout << data[i]; 
                if (i != size - 1) { 
                    cout << ", "; 
                }
            }
            cout << "]" << endl;
        }

        vector<int> get_time_taken(vector<T> api, vector<T> data) {
            vector<int> time_for_ds;
            for(auto method : api) {
                auto start = chrono::high_resolution_clock::now();

                if(method == "insert()") {
                    for(size_t i = 0; i < data.size(); i++){
                        append(data.at(i));
                    }
                }
                else if(method == "delete()") {
                    for(size_t i = (data.size()/2); i < data.size(); i++){
                        remove(i);
                        append(data.at(i));
                    }
                    
                }
                else if(method == "search()") {
                    search(data.back());
                }
                else if(method == "size()") {
                    int x = getSize();
                }
                else if(method == "sort()") {
                    sort();
                }
                auto stop = chrono::high_resolution_clock::now();

                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

                time_for_ds.push_back(duration.count());
            }
            return time_for_ds;
        }
};