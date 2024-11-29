#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

// A class template for dynamic stacks using vector
template <class T>
class Stack {
    private:
        vector<T> data; // The underlying vector to store the elements
        int size; // The current number of elements in the stack
        int capacity; // The maximum number of elements the stack can hold

    public:
        // A default constructor that creates an empty stack
        Stack() {
            size = 0;
            capacity = 10;
            data.resize(capacity); // Allocate memory for the vector
        }

        // A parameterized constructor that creates a stack with a given capacity
        Stack(int n) {
            size = 0;
            capacity = n;
            data.resize(capacity); // Allocate memory for the vector
        }

        // A copy constructor that creates a deep copy of another stack
        Stack(const Stack<T>& other) {
            size = other.size;
            capacity = other.capacity;
            data.resize(capacity); // Allocate memory for the vector
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i]; // Copy each element from the other stack
            }
        }

        // A destructor that frees the memory allocated by the vector
        ~Stack() {
            data.clear(); // Clear the vector
        }

        // An assignment operator that assigns the contents of another stack to this stack
        Stack<T>& operator=(const Stack<T>& other) {
            if (this != &other) { // Avoid self-assignment
                size = other.size;
                capacity = other.capacity;
                data.resize(capacity); // Allocate memory for the vector
                for (int i = 0; i < size; i++) {
                    data[i] = other.data[i]; // Copy each element from the other stack
                }
            }
            return *this; // Return a reference to this stack
        }

        // A method that returns the current number of elements in the stack
        int getSize() const {
            return size;
        }

        // A method that returns the maximum number of elements the stack can hold
        int getCapacity() const {
            return capacity;
        }

        // A method that checks if the stack is empty or not
        bool isEmpty() const {
            return size == 0;
        }

        // A method that checks if the stack is full or not
        bool isFull() const {
            return size == capacity;
        }

        // A method that adds a new element at the top of the stack, resizing it if necessary
        void push(T val) {
            if (size == capacity) { // Check if the stack is full
                capacity *= 2; // Double the capacity
                data.resize(capacity); // Resize the vector accordingly
            }
            data[size] = val; // Assign the new value to the top position
            size++; // Increment the size by one
        }

        // A method that removes and returns an element from the top of the stack, throwing an exception if it is empty 
        T pop() {
            if (size > 0) { // Check if the stack is not empty 
                size--; // Decrement the size by one 
                return data[size]; // Return the value at the top position 
            }
            else { // Throw an exception if the stack is empty 
                throw out_of_range("Stack underflow");
            }
        }

        // A method that returns an element from the top of the stack without removing it, throwing an exception if it is empty 
        T peek() const {
            if (size > 0) { // Check if the stack is not empty 
                return data[size - 1]; // Return the value at the top position 
            }
            else { // Throw an exception if the stack is empty 
                throw out_of_range("Stack underflow");
            }
        }

        // A method to search for an element in the stack using linear search
        int search(T element) {
            for (int i = 0; i < size; i++) { // loop through the stack elements from bottom to top
                if (data[i] == element) { // if the current element is equal to the target element, return its index
                    return i;
                }
            }
            return -1; // if the element is not found, return -1
        }

        // A method to reverse the stack elements using another stack as a temporary storage
        void reverse() {
            Stack<T> temp(capacity); // create a temporary stack with the same capacity
            while (!isEmpty()) { // while the original stack is not empty
                temp.push(pop()); // pop an element from the original stack and push it onto the temporary stack
            }
            data = temp.data; // assign the data vector of the temporary stack to the original stack
        }

        // A method that prints all the elements in the stack from top to bottom 
        void print() const {
            cout << "[";
            for (int i = size - 1; i >= 0; i--) {
                cout << data[i]; 
                if (i != 0) { 
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
                        push(data.at(i));
                    }
                }
                else if(method == "delete()") {
                    for(size_t i = (data.size()/2); i < data.size(); i++){
                        pop();
                        push(data.at(i));
                    }
                    
                }
                else if(method == "search()") {
                    search(data.back());
                }
                else if(method == "size()") {
                    int x = getSize();
                }
                else if(method == "sort()") {
                    reverse();
                }
                auto stop = chrono::high_resolution_clock::now();

                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

                time_for_ds.push_back(duration.count());
            }
            return time_for_ds;
        }
};
