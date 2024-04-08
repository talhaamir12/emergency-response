#include <iostream>
#include <list>
#include <unordered_map>

// define your classes here...
class Edge {
private:


public:
    double d; // d is distance between intersection in meters
    double S; // S is the speed limit on the road linking them
    double A; // A is the adjustment factor, [0-1] A = 0 means blocked
    Edge(double distance, double speedLimit, double adjustment = 1.0); // Constructor
    Edge(); // Default constructor
    double time() const;
    
};

class Graph {
private:
    std::unordered_map<int, std::unordered_map<int, Edge>> graph;
    std::unordered_map<int, double> distances; // to store distances from source
    std::unordered_map<int, int> parents; // to store parent of each node


public:
    bool insert(int v1, int v2, double d, double S); // for inserting a new edge into the graph from vertex 'a' to 'b' with distance 'd' and speed limit 's'
    bool traffic(int v1, int v2, double A); // for updating the adjustment factor to A for the edge between vertices 'a' and 'b'
    void print(int v1); // for printing all vertices adjacent to vertex 'a' on a single line with spaces between them
    bool delete_vertex(int v1); // for deleting the vertex 'a' and clearing any edges containing 'a'
    void path(int v1, int v2); // for printing all vertices along the lowest weight path between vertices 'a' and 'b'
    void lowest(int v1, int v2); // for printing the weight (x) of the lowest weight path between vertices 'a' and 'b'
    void dijkstras_algorithm(int source);

};