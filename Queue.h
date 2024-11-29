#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// A class template for dynamic queues using vector
/// @brief 
/// @tparam T 
template <class T>

class DynamicQueue {
    private:
        vector<T> data; // The underlying vector to store the elements
        int size; // The current number of elements in the queue
        int capacity; // The maximum number of elements the queue can hold
        int front; // The index of the front element in the queue
        int rear; // The index of the rear element in the queue

    public:
        // A default constructor that creates an empty queue
        DynamicQueue() {
            size = 0;
            capacity = 10;
            data.resize(capacity); // Allocate memory for the vector
            front = 0;
            rear = -1;
        }

        // A parameterized constructor that creates a queue with a given capacity
        DynamicQueue(int n) {
            size = 0;
            capacity = n;
            data.resize(capacity); // Allocate memory for the vector
            front = 0;
            rear = -1;
        }

        // A copy constructor that creates a deep copy of another queue
        DynamicQueue(const DynamicQueue<T>& other) {
            size = other.size;
            capacity = other.capacity;
            data.resize(capacity); // Allocate memory for the vector
            front = other.front;
            rear = other.rear;
            for (int i = 0; i < size; i++) {
                data[(front + i) % capacity] = other.data[(front + i) % capacity]; // Copy each element from the other queue using modular arithmetic
            }
        }

        // A destructor that frees the memory allocated by the vector
        ~DynamicQueue() {
            data.clear(); // Clear the vector
        }

        // An assignment operator that assigns the contents of another queue to this queue
        DynamicQueue<T>& operator=(const DynamicQueue<T>& other) {
            if (this != &other) { // Avoid self-assignment
                size = other.size;
                capacity = other.capacity;
                data.resize(capacity); // Allocate memory for the vector
                front = other.front;
                rear = other.rear;
                for (int i = 0; i < size; i++) {
                    data[(front + i) % capacity] = other.data[(front + i) % capacity]; // Copy each element from the other queue using modular arithmetic
                }
            }
            return *this; // Return a reference to this queue
        }

        // A method that returns the current number of elements in the queue
        int getSize() const {
            return size;
        }

        // A method that returns the maximum number of elements the queue can hold
        int getCapacity() const {
            return capacity;
        }

        // A method that checks if the queue is empty or not
        bool isEmpty() const {
            return size == 0;
        }

        // A method that checks if the queue is full or not
        bool isFull() const {
            return size == capacity;
        }

        // A method that adds a new element at the rear of the queue, resizing it if necessary
        void enqueue(T val) {
            if (size == capacity) { // Check if the queue is full
                capacity *= 2; // Double the capacity
                vector<T> temp(capacity); // Create a temporary vector with the new capacity
                for (int i = 0; i < size; i++) {
                    temp[i] = data[(front + i) % size]; // Copy each element from the old vector to the new one using modular arithmetic 
                }
                data = temp; // Assign the new vector to the old one 
                front = 0; // Reset the front index 
                rear = size - 1; // Reset the rear index 
            }
            rear = (rear + 1) % capacity; // Increment the rear index using modular arithmetic 
            data[rear] = val; // Assign the new value to the rear position 
            size++; // Increment the size by one 
        }

        // A method that removes and returns an element from the front of the queue, throwing an exception if it is empty 
        T dequeue() {
            if (size > 0) { // Check if the queue is not empty 
                T val = data[front]; // Store the value at the front position 
                front = (front + 1) % capacity; // Increment the front index using modular arithmetic 
                size--; // Decrement the size by one 
                return val; // Return the value 
            }
            else { // Throw an exception if the queue is empty 
                throw out_of_range("Queue underflow");
            }
        }

        // A method that returns an element from the front of the queue without removing it, throwing an exception if it is empty 
        T peek() const {
            if (size > 0) { // Check if the queue is not empty 
                return data[front]; // Return the value at the front position 
            }
            else { // Throw an exception if the queue is empty 
                throw out_of_range("Queue underflow");
            }
        }

        // A method to search for an element in the queue using linear search
        int search(T element) {
            for (int i = 0; i < size; i++) { // loop through the queue elements from front to rear in a circular way
                int index = (front + i) % capacity; // calculate the actual index in the vector
                if (data[index] == element) { // if the current element is equal to the target element, return its index
                    return index;
                }
            }
            return -1; // if the element is not found, return -1
        }

        // A method to sort the queue elements in ascending order using selection sort
        void sort() {
            for (int i = 0; i < size - 1; i++) { // loop through the queue from 0 to size - 2
                int minIndex = i; // assume the current element is the minimum
                for (int j = i + 1; j < size; j++) { // loop through the queue from i + 1 to size - 1
                    int index1 = (front + minIndex) % capacity; // calculate the actual index of the minimum element in the vector
                    int index2 = (front + j) % capacity; // calculate the actual index of the current element in the vector
                    if (data[index2] < data[index1]) { // if the current element is less than the minimum element, update the minimum index
                        minIndex = j;
                    }
                }
                if (minIndex != i) { // if the minimum index is not equal to the current index, swap them
                    int index1 = (front + i) % capacity; // calculate the actual index of the current element in the vector
                    int index2 = (front + minIndex) % capacity; // calculate the actual index of the minimum element in the vector
                    T temp = data[index1];
                    data[index1] = data[index2];
                    data[index2] = temp;
                }
            }
        }

        // A method that prints all the elements in the queue from front to rear 
        void print() const {
            cout << "[";
            for (int i = 0; i < size; i++) {
                cout << data[(front + i) % capacity]; 
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
                        enqueue(data.at(i));
                    }
                }
                else if(method == "delete()") {
                    for(size_t i = (data.size()/2); i < data.size(); i++){
                        dequeue();
                        enqueue(data.at(i));
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
