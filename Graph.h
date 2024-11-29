#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// A class template for graphs using adjacency lists
template <class T>
class Graph {
    private:
        int numVertices; // The number of vertices in the graph
        vector<vector<T>> adjList; // The vector of vectors to store the adjacency lists of each vertex

        // A helper method that performs a depth-first traversal from a given vertex, marking the visited vertices in a vector
        void dfsHelper(int v, vector<bool>& visited) {
            visited[v] = true; // Mark the current vertex as visited
            cout << v << " "; // Print the current vertex
            for (T u : adjList[v]) { // Loop through the adjacent vertices of the current vertex
                if (!visited[u]) { // Check if the adjacent vertex is not visited
                    dfsHelper(u, visited); // Recursively traverse from the adjacent vertex
                }
            }
        }

        // A helper method that performs a breadth-first traversal from a given vertex, marking the visited vertices in a vector
        void bfsHelper(int v, vector<bool>& visited) {
            queue<int> q; // Create an empty queue to store the vertices to be visited
            q.push(v); // Enqueue the current vertex
            visited[v] = true; // Mark the current vertex as visited
            while (!q.empty()) { // Loop until the queue is empty
                int u = q.front(); // Dequeue a vertex from the queue and store it in a variable
                q.pop();
                cout << u << " "; // Print the dequeued vertex
                for (T w : adjList[u]) { // Loop through the adjacent vertices of the dequeued vertex
                    if (!visited[w]) { // Check if the adjacent vertex is not visited
                        q.push(w); // Enqueue the adjacent vertex
                        visited[w] = true; // Mark the adjacent vertex as visited
                    }
                }
            }
        }

    public:
        // A constructor that creates a graph with a given number of vertices and no edges
        Graph(int n) {
            numVertices = n;
            adjList.resize(n); // Resize the vector of vectors to have n vectors, one for each vertex
        }

        // A method that adds an edge between two given vertices in the graph, assuming it is undirected and unweighted
        void addEdge(T u, T v) {
            adjList[u].push_back(v); // Add v to the adjacency list of u
            adjList[v].push_back(u); // Add u to the adjacency list of v
        }

        // A method that prints all vertices and their adjacency lists in the graph
        void print() const {
            for (int i = 0; i < numVertices; i++) { // Loop through all vertices in the graph
                cout << i << ": "; // Print the current vertex
                for (T j : adjList[i]) { // Loop through the adjacency list of the current vertex
                    cout << j << " "; // Print each adjacent vertex 
                }
                cout << endl;
            }
        }

        // A method that performs a depth-first traversal from a given vertex in the graph and prints all visited vertices 
        void dfs(int v) {
            vector<bool> visited(numVertices, false); // Create a vector of booleans to store whether each vertex is visited or not, initialized to false 
            dfsHelper(v, visited); // Call the helper method to traverse from the given vertex 
            cout << endl;
        }

        // A method that performs a breadth-first traversal from a given vertex in the graph and prints all visited vertices 
        void bfs(int v) {
            vector<bool> visited(numVertices, false); // Create a vector of booleans to store whether each vertex is visited or not, initialized to false 
            bfsHelper(v, visited); // Call the helper method to traverse from the given vertex 
            cout << endl;
        }

        // A method to sort the values in the graph
        void sort() {
            reset(); // Reset the visited flag of all nodes
            std::vector<T> sorted; // Create a vector to store the sorted values
            for (GraphNode<T>* node : nodes) { // Loop through the nodes in the graph
                if (!node->visited) { // If the node has not been visited
                    sort(node, sorted); // Call the helper method on the node and the vector
                }
            }
            for (int i = 0; i < nodes.size(); i++) { // Loop through the nodes in the graph
                nodes[i]->data = sorted[i]; // Assign the sorted values to the nodes
            }
        }

        // A helper method to sort the values in the subtree rooted at a given node using depth-first search
        void sort(GraphNode<T>* node, std::vector<T>& sorted) {
            node->visited = true; // Mark the node as visited
            for (GraphNode<T>* neighbor : node->neighbors) { // Loop through the neighbors of the node
                if (!neighbor->visited) { // If the neighbor has not been visited
                    sort(neighbor, sorted); // Recursively sort the neighbor and its subtree
                }
            }
            sorted.push_back(node->data); // Add the node's data to the vector
        }

        // A method to search for a value in the graph
        bool search(T value) const {
            reset(); // Reset the visited flag of all nodes
            for (GraphNode<T>* node : nodes) { // Loop through the nodes in the graph
                if (!node->visited) { // If the node has not been visited
                    if (search(node, value)) { // Call the helper method on the node and the value
                        return true; // If the value is found, return true
                    }
                }
            }
            return false; // If the value is not found, return false
        }

        // A helper method to search for a value in the subtree rooted at a given node using depth-first search
        bool search(GraphNode<T>* node, T value) const {
            node->visited = true; // Mark the node as visited
            if (node->data == value) { // If the node's data matches the value
                return true; // The value is found
            }
            for (GraphNode<T>* neighbor : node->neighbors) { // Loop through the neighbors of the node
                if (!neighbor->visited) { // If the neighbor has not been visited
                    if (search(neighbor, value)) { // Recursively search for the value in the neighbor and its subtree
                        return true; // If the value is found, return true
                    }
                }
            }
            return false; // The value is not found
        }

        // A method to reverse the order of the edges in the graph
        void reverse() {
            for (GraphNode<T>* node : nodes) { // Loop through the nodes in the graph
                std::reverse(node->neighbors.begin(), node->neighbors.end()); // Reverse the order of the neighbors vector
            }
        }


};
