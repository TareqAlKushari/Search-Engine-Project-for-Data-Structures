#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// A class template for linked list nodes
template <class T>
class Node {
    public:
        T data; // The data stored in the node
        Node<T>* next; // The pointer to the next node

        // A constructor that creates a node with a given data and next pointer
        Node(T val, Node<T>* ptr = nullptr) {
            data = val;
            next = ptr;
        }
};

// A class template for linked lists
template <class T>
class LinkedList {
    private:
        Node<T>* head; // The pointer to the head node of the list
        Node<T>* tail; // The pointer to the tail node of the list
        int size; // The current number of nodes in the list

    public:
        // A default constructor that creates an empty list
        LinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        // A copy constructor that creates a deep copy of another list
        LinkedList(const LinkedList<T>& other) {
            head = nullptr;
            tail = nullptr;
            size = 0;
            Node<T>* temp = other.head; // A temporary pointer to traverse the other list
            while (temp != nullptr) { // Loop until the end of the other list
                append(temp->data); // Append the data of the current node to this list
                temp = temp->next; // Move to the next node in the other list
            }
        }

        // A destructor that frees the memory allocated by the nodes
        ~LinkedList() {
            clear(); // Clear the list
        }

        // An assignment operator that assigns the contents of another list to this list
        LinkedList<T>& operator=(const LinkedList<T>& other) {
            if (this != &other) { // Avoid self-assignment
                clear(); // Clear this list
                Node<T>* temp = other.head; // A temporary pointer to traverse the other list
                while (temp != nullptr) { // Loop until the end of the other list
                    append(temp->data); // Append the data of the current node to this list
                    temp = temp->next; // Move to the next node in the other list
                }
            }
            return *this; // Return a reference to this list
        }

        // An index operator that returns a reference to the data at a given position, throwing an exception if it is out of bounds 
        T& operator[](int index) {
            if (index >= 0 && index < size) { // Check if the index is valid 
                Node<T>* temp = head; // A temporary pointer to traverse the list 
                for (int i = 0; i < index; i++) { 
                    temp = temp->next; // Move to the next node until reaching the desired position 
                }
                return temp->data; // Return a reference to the data at that position 
            }
            else { // Throw an exception if the index is out of bounds 
                throw out_of_range("Index out of bounds");
            }
        }

        // A const index operator that returns a const reference to the data at a given position, throwing an exception if it is out of bounds 
        const T& operator[](int index) const {
            if (index >= 0 && index < size) { // Check if the index is valid 
                Node<T>* temp = head; // A temporary pointer to traverse the list 
                for (int i = 0; i < index; i++) { 
                    temp = temp->next; // Move to the next node until reaching the desired position 
                }
                return temp->data; // Return a const reference to the data at that position 
            }
            else { // Throw an exception if the index is out of bounds 
                throw out_of_range("Index out of bounds");
            }
        }

        // A method that returns the current number of nodes in the list
        int getSize() const {
            return size;
        }

        // A method that checks if the list is empty or not
        bool isEmpty() const {
            return size == 0;
        }

        // A method that adds a new node at the end of the list, containing a given data
        void append(T val) {
            Node<T>* newNode = new Node<T>(val); // Create a new node with the given data and null pointer
            if (head == nullptr) { // Check if the list is empty
                head = newNode; // Make the new node as the head node
                tail = newNode; // Make the new node as the tail node
            }
            else { // If the list is not empty
                tail->next = newNode; // Make the new node as the next node of the tail node
                tail = newNode; // Make the new node as the tail node
            }
            size++; // Increment the size by one
        }

        // A method that inserts a new node at a given position, containing a given data, shifting the existing nodes to the right 
        void insert(int index, T val) {
            if (index >= 0 && index <= size) { // Check if the index is valid 
                Node<T>* newNode = new Node<T>(val); // Create a new node with the given data and null pointer 
                if (index == 0) { // Check if inserting at the beginning of the list 
                    newNode->next = head; // Make the new node as the next node of head 
                    head = newNode; // Make head point to new node 
                    if (tail == nullptr) { // Check if tail is null (list was empty)
                        tail = newNode;
                                        }
                }
                else if (index == size) { // Check if inserting at the end of the list 
                    tail->next = newNode; // Make the new node as the next node of tail 
                    tail = newNode; // Make tail point to new node 
                }
                else { // If inserting in the middle of the list 
                    Node<T>* temp = head; // A temporary pointer to traverse the list 
                    for (int i = 0; i < index - 1; i++) { 
                        temp = temp->next; // Move to the next node until reaching the node before the desired position 
                    }
                    newNode->next = temp->next; // Make the new node as the next node of the current node 
                    temp->next = newNode; // Make the current node as the next node of the new node 
                }
                size++; // Increment the size by one 
            }
            else { // Throw an exception if the index is out of bounds 
                throw out_of_range("Index out of bounds");
            }
        }

        // A method that removes and returns a node at a given position, shifting the existing nodes to the left 
        T remove(int index) {
            if (index >= 0 && index < size) { // Check if the index is valid 
                T val; // A variable to store the data of the removed node 
                if (index == 0) { // Check if removing from the beginning of the list 
                    Node<T>* temp = head; // A temporary pointer to store the head node 
                    val = temp->data; // Store the data of the head node 
                    head = head->next; // Make head point to the next node 
                    delete temp; // Delete the old head node 
                    if (head == nullptr) { // Check if head is null (list became empty)
                        tail = nullptr;
                    }
                }
                else { // If removing from the middle or end of the list 
                    Node<T>* prev = head; // A pointer to store the previous node of the current node 
                    for (int i = 0; i < index - 1; i++) { 
                        prev = prev->next; // Move to the next node until reaching the node before the desired position
                    }
                    Node<T>* curr = prev->next; // A pointer to store the current node at the desired position
                    val = curr->data; // Store the data of the current node
                    prev->next = curr->next; // Make the previous node as the next node of the current node
                    delete curr; // Delete the current node
                    if (prev->next == nullptr) { // Check if prev is now pointing to null (removed from end of list)
                        tail = prev;
                    }
                }
                size--; // Decrement the size by one
                return val; // Return the data of the removed node
            }
            else { // Throw an exception if the index is out of bounds
                throw out_of_range("Index out of bounds");
            }
        }

        // A method that searches for a given data in the list and returns its position, or -1 if not found
        int search(T val) const {
            Node<T>* temp = head; // A temporary pointer to traverse the list
            int index = 0; // A variable to store the current index
            while (temp != nullptr) { // Loop until reaching null
                if (temp->data == val) { // Check if the data of the current node matches the given value
                    return index; // Return the index
                }
                temp = temp->next; // Move to the next node
                index++; // Increment the index by one
            }
            return -1; // Return -1 if not found
        }

        // A helper method to insert a node into a sorted list in its correct position
        Node<T>* insertSorted(Node<T>* sortedHead, Node<T>* newNode) {
            if (sortedHead == NULL || newNode->data <= sortedHead->data) { // if the sorted list is empty or the new node is smaller than or equal to the head node of the sorted list, link the new node before the head node and return it as the new head
                newNode->next = sortedHead;
                return newNode;
            } else { // otherwise, find the previous node of the position where the new node should be inserted and link it after that node
                Node<T>* prevNode = sortedHead; // start from the head node of the sorted list
                while (prevNode->next != NULL && prevNode->next->data < newNode->data) { // loop until reaching the previous node or the end of the sorted list
                    prevNode = prevNode->next;
                }
                newNode->next = prevNode->next; // link the new node after the previous node
                prevNode->next = newNode;
                return sortedHead; // return the head of the sorted list
            }
        }

        // A helper method to get the tail node of a list
        Node<T>* getTail() {
            Node<T>* currNode = head; // start from the head node
            while (currNode != NULL && currNode->next != NULL) { // loop until reaching the last node or NULL
                currNode = currNode->next;
            }
            return currNode; // return the last node or NULL
        }

        // A method to sort the list elements in ascending order using insertion sort
        void sort() {
            Node<T>* sortedHead = NULL; // a pointer to store the head of the sorted list
            Node<T>* currNode = head; // a pointer to store the current node of the original list
            while (currNode != NULL) { // loop until reaching the end of the original list
                Node<T>* nextNode = currNode->next; // store the next node of the current node
                sortedHead = insertSorted(sortedHead, currNode); // insert the current node into the sorted list in its correct position
                currNode = nextNode; // move on to the next node of the original list
            }
            head = sortedHead; // update the head pointer of the original list to point to the sorted list
            tail = getTail(); // update the tail pointer of the original list to point to the last node of the sorted list
        }

        // A method to reverse the list elements using three pointers
        void reverse() {
            Node<T>* prevNode = NULL; // a pointer to store the previous node
            Node<T>* currNode = head; // a pointer to store the current node
            Node<T>* nextNode = NULL; // a pointer to store the next node
            while (currNode != NULL) { // loop until reaching the end of the list
                nextNode = currNode->next; // store the next node of the current node
                currNode->next = prevNode; // link the current node to the previous node
                prevNode = currNode; // move the previous node to the current node
                currNode = nextNode; // move the current node to the next node
            }
            head = prevNode; // update the head pointer to point to the last node of the original list
            tail = getTail(); // update the tail pointer to point to the first node of the original list
        }

        // A method that clears all nodes from the list
        void clear() {
            Node<T>* temp = head; // A temporary pointer to traverse and delete nodes
            while (temp != nullptr) { // Loop until reaching null
                Node<T>* next = temp->next; // Store a pointer to next node
                delete temp; // Delete current node
                temp = next; // Move to next node
            }
            head = nullptr; // Reset head pointer
            tail = nullptr; // Reset tail pointer
            size = 0; // Reset size
        }

        // A method that prints all data in the list from head to tail
        void print() const {
            cout << "[";
            Node<T>* temp = head; // A temporary pointer to traverse and print nodes
            while (temp != nullptr) { // Loop until reaching null
                cout << temp->data;
                if (temp->next != nullptr) { // Check if not last element
                    cout << ", ";
                }
                temp = temp->next; // Move to next node
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
