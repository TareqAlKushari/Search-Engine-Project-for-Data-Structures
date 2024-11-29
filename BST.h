#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

// A class template for binary search tree nodes
template <class T>

class BSTNode {
    public:
        T data; // The data stored in the node
        BSTNode<T>* left; // The pointer to the left child node
        BSTNode<T>* right; // The pointer to the right child node

        // A constructor that creates a node with a given data and null pointers
        BSTNode(T val) {
            data = val;
            left = nullptr;
            right = nullptr;
        }
};

// A class template for binary search trees
template <class T>

class BST {
    private:
        BSTNode<T>* root; // The pointer to the root node of the tree

        // A helper method that inserts a new node with a given data into a subtree rooted at a given node
        void insertHelper(BSTNode<T>*& node, T val) {
            if (node == nullptr) { // Check if the subtree is empty
                node = new BSTNode<T>(val); // Create a new node with the given data and null pointers and assign it to the subtree
            }
            else if (val < node->data) { // Check if the given data is less than the data of the current node
                insertHelper(node->left, val); // Recursively insert into the left subtree
            }
            else if (val > node->data) { // Check if the given data is greater than the data of the current node
                insertHelper(node->right, val); // Recursively insert into the right subtree
            }
            else { // If the given data is equal to the data of the current node, do nothing (no duplicates allowed)
                return;
            }
        }

        // A helper method that searches for a given data in a subtree rooted at a given node and returns true if found, false otherwise
        bool searchHelper(BSTNode<T>* node, T val) const {
            if (node == nullptr) { // Check if the subtree is empty
                return false; // Return false
            }
            else if (val < node->data) { // Check if the given data is less than the data of the current node
                return searchHelper(node->left, val); // Recursively search in the left subtree
            }
            else if (val > node->data) { // Check if the given data is greater than the data of the current node
                return searchHelper(node->right, val); // Recursively search in the right subtree
            }
            else { // If the given data is equal to the data of the current node
                return true; // Return true
            }
        }

        // A helper method that finds and returns the minimum value in a subtree rooted at a given node
        T findMin(BSTNode<T>* node) const {
            if (node == nullptr) { // Check if the subtree is empty
                throw logic_error("Tree is empty"); // Throw an exception
            }
            else if (node->left == nullptr) { // Check if there is no left child of the current node
                return node->data; // Return the data of the current node as the minimum value
            }
            else { // If there is a left child of the current node
                return findMin(node->left); // Recursively find the minimum value in the left subtree
            }
        }

        // A helper method that finds and returns the maximum value in a subtree rooted at a given node
        T findMax(BSTNode<T>* node) const {
            if (node == nullptr) { // Check if the subtree is empty
                throw logic_error("Tree is empty"); // Throw an exception
            }
            else if (node->right == nullptr) { // Check if there is no right child of the current node
                return node->data; // Return the data of the current node as the maximum value
            }
            else { // If there is a right child of the current node
                return findMax(node->right); // Recursively find the maximum value in the right subtree
            }
        }

        // A helper method that removes a node with a given data from a subtree rooted at a given node and returns the new root of the subtree
        BSTNode<T>* removeHelper(BSTNode<T>* node, T val) {
            if (node == nullptr) { // Check if the subtree is empty
                return nullptr; // Return null
            }
            else if (val < node->data) { // Check if the given data is less than the data of the current node
                node->left = removeHelper(node->left, val); // Recursively remove from the left subtree and update the left pointer of the current node
            }
            else if (val > node->data) { // Check if the given data is greater than the data of the current node
                node->right = removeHelper(node->right, val); // Recursively remove from the right subtree and update the right pointer of the current node
            }
            else { // If the given data is equal to the data of the current node
                if (node->left == nullptr && node->right == nullptr) { // Check if the current node has no children
                    delete node; // Delete the current node
                    return nullptr; // Return null
                }
                else if (node->left == nullptr) { // Check if the current node has only a right child
                    BSTNode<T>* temp = node->right; // Store a pointer to the right child
                    delete node; // Delete the current node
                    return temp; // Return the right child as the new root of the subtree
                }
                else if (node->right == nullptr) { // Check if the current node has only a left child
                    BSTNode<T>* temp = node->left; // Store a pointer to the left child
                    delete node; // Delete the current node
                    return temp; // Return the left child as the new root of the subtree
                }
                else { // If the current node has two children
                    T minVal = findMin(node->right); // Find and store the minimum value in the right subtree
                    node->data = minVal; // Replace the data of the current node with that value
                    node->right = removeHelper(node->right, minVal); // Recursively remove that value from the right subtree and update the right pointer of the current node 
                }
            }
            return node; // Return the current node as the new root of the subtree 
        }

        // A helper method that prints all data in a subtree rooted at a given node in inorder traversal (left, root, right)
        void printInorder(BSTNode<T>* node) const {
            if (node != nullptr) { // Check if the subtree is not empty 
                printInorder(node->left); // Recursively print in inorder traversal from left subtree 
                cout << node->data << " "; // Print data of current node 
                printInorder(node->right); // Recursively print in inorder traversal from right subtree 
            }
        }

        // A helper method that prints all data in a subtree rooted at a given node in preorder traversal (root, left, right)
        void printPreorder(BSTNode<T>* node) const {
            if (node != nullptr) { // Check if the subtree is not empty 
                cout << node->data << " "; // Print data of current node 
                printPreorder(node->left); // Recursively print in preorder traversal from left subtree 
                printPreorder(node->right); // Recursively print in preorder traversal from right subtree 
            }
        }

        // A helper method that prints all data in a subtree rooted at a given node in postorder traversal (left, right, root)
        void printPostorder(BSTNode<T>* node) const {
            if (node != nullptr) { // Check if the subtree is not empty 
                printPostorder(node->left); // Recursively print in postorder traversal from left subtree 
                printPostorder(node->right); // Recursively print in postorder traversal from right subtree 
                cout << node->data << " "; // Print data of current node 
            }
        }

    public:
        // A default constructor that creates an empty tree
        BST() {
            root = nullptr;
        }

        // A destructor that clears all nodes from the tree
        ~BST() {
            clear(); 
        }

        // A method that inserts a new data into the tree, maintaining its binary search property
        void insert(T val) {
            insertHelper(root, val);             // Call the helper method to insert into the subtree rooted at root
        }

        // A method that searches for a given data in the tree and returns true if found, false otherwise
        bool search(T val) const {
            return searchHelper(root, val); // Call the helper method to search in the subtree rooted at root
        }

        // A method that finds and returns the minimum value in the tree, throwing an exception if it is empty
        T findMin() const {
            return findMin(root); // Call the helper method to find the minimum value in the subtree rooted at root
        }

        // A method that finds and returns the maximum value in the tree, throwing an exception if it is empty
        T findMax() const {
            return findMax(root); // Call the helper method to find the maximum value in the subtree rooted at root
        }

        // A method that removes a given data from the tree, maintaining its binary search property
        void remove(T val) {
            root = removeHelper(root, val); // Call the helper method to remove from the subtree rooted at root and update the root pointer
        }

        // A method that clears all nodes from the tree
        void clear() {
            while (root != nullptr) { // Loop until the tree is empty
                remove(root->data); // Remove the data of the root node
            }
        }

        // A method to sort the values in the BST
        void sort() {
            sort(root); // Call the helper method on the root node
        }

        // A helper method to sort the values in the subtree rooted at a given node
        void sort(BSTNode<T>* node) {
            if (node == nullptr) { // Base case: the subtree is empty
                return; // Do nothing
            }
            else { // Recursive case: the subtree is not empty
                // Sort the values in the left and right subtrees
                sort(node->left);
                sort(node->right);

                // Move the node's data to its correct position in the subtree
                T value = node->data; // Store the node's data
                BSTNode<T>* curr = node; // Initialize a pointer to the node
                while (curr->left != nullptr && value < curr->left->data) { // While the node has a left child and its data is smaller than the left child's data
                    curr->data = curr->left->data; // Copy the left child's data to the node
                    curr = curr->left; // Move the pointer to the left child
                }
                curr->data = value; // Copy the stored data to its correct position
            }
        }

        // A method to reverse the order of the nodes in the BST
        void reverse() {
            reverse(root); // Call the helper method on the root node
        }

        // A helper method to reverse the order of the nodes in the subtree rooted at a given node
        void reverse(BSTNode<T>* node) {
            if (node == nullptr) { // Base case: the subtree is empty
                return; // Do nothing
            }
            else { // Recursive case: the subtree is not empty
                // Swap the left and right pointers of the node
                BSTNode<T>* temp = node->left;
                node->left = node->right;
                node->right = temp;

                // Reverse the order of the nodes in the left and right subtrees
                reverse(node->left);
                reverse(node->right);
            }
        }


        // A method that prints all data in the tree in inorder traversal (left, root, right)
        void printInorder() const {
            printInorder(root); // Call the helper method to print in inorder traversal from the subtree rooted at root
            cout << endl;
        }

        // A method that prints all data in the tree in preorder traversal (root, left, right)
        void printPreorder() const {
            printPreorder(root); // Call the helper method to print in preorder traversal from the subtree rooted at root
            cout << endl;
        }

        // A method that prints all data in the tree in postorder traversal (left, right, root)
        void printPostorder() const {
            printPostorder(root); // Call the helper method to print in postorder traversal from the subtree rooted at root
            cout << endl;
        }

        vector<int> get_time_taken(vector<T> api, vector<T> data) {
            vector<int> time_for_ds;
            for(auto method : api) {
                auto start = chrono::high_resolution_clock::now();

                if(method == "insert()") {
                    for(size_t i = 0; i < data.size(); i++){
                        insert(data.at(i));
                    }
                }
                else if(method == "delete()") {
                    for(size_t i = (data.size()/2); i < data.size(); i++){
                        remove(data.at(i));
                        insert(data.at(i));
                    }
                    
                }
                else if(method == "search()") {
                    search(data.back());
                }
                else if(method == "size()") {
                    T x = findMax();
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
