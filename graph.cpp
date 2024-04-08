#include "graph.h"
#include <limits>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_map>

// implement classes' member functions here...

bool Graph::insert(int v1, int v2, double d, double S) {

    if (graph[v1].find(v2) != graph[v1].end()) {
            graph[v1][v2].d = d;
            graph[v1][v2].S = S;
            graph[v2][v1].d = d;
            graph[v2][v1].S = S;
            return true;
        }

    // Adding the edges
    graph[v1][v2] = Edge(d, S);
    graph[v2][v1] = Edge(d, S);

    return true;

}


bool Graph::traffic(int v1, int v2, double A) {
    // Check if both vertices dont exist
    if (graph.find(v1) == graph.end() || graph.find(v2) == graph.end()) {
        return false; // If at least one vertex doesnt exist then return false
    }
    // Check for an edge between the vertices
    if (graph[v1].find(v2) == graph[v1].end()) {
        return false;
    }
    // Update adjustment factor for the edges
    graph[v1][v2].A = A;
    graph[v2][v1].A = A;

    return true;

}

void Graph::print(int v1) {
    // Check if vertex exists
    if (graph.find(v1) == graph.end()) {
        std::cout << "failure" << std::endl;
        return;
    }

    for (const auto& pair : graph[v1]) {
        std::cout << pair.first << " "; // print adjacent vertex
    }
    std::cout << std::endl;;

}


bool Graph::delete_vertex(int v1) {

    // Check if vertex exists
    if (graph.find(v1) == graph.end()) {
        return false;
    }

    // Iterate through vertices that are adjacent to v1 and remove v1 from their adjacency list
    for (const auto& adj : graph.find(v1)->second) {
        int v2 = adj.first;
        graph[v2].erase(v1); // Remove edge from v2 to v1
    }

    // Remove v1 after removing it from its adjacency list of neighbours
    graph.erase(v1);

    return true;
}


void Graph::path(int v1, int v2) {

    // Check if the target can be reached, if not, print failure and return.
    if (distances.find(v2) == distances.end() || distances[v2] == std::numeric_limits<double>::infinity()) {
        std::cout << "failure" << std::endl;
        return;
    }

    dijkstras_algorithm(v1); // Run Dijkstra's algorithm from the source



    // Reconstruct the shortest path from target to source using the parents map
    std::vector<int> shortest;
    for (int vertex = v2; vertex != -1; vertex = parents[vertex]) {
        shortest.push_back(vertex);
    }
    std::reverse(shortest.begin(), shortest.end()); // Reverse to get the path from source to target

    // Output the shortest path
    for (int vertex : shortest) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}


void Graph::lowest(int v1, int v2) {

    // Check if the target is reachable, if not, print failure and return
    if (distances.find(v2) == distances.end() || distances[v2] == std::numeric_limits<double>::infinity()) {
        std::cout << "failure" << std::endl;
        return;
    }
    dijkstras_algorithm(v1); // Run Dijkstra's algorithm from the source


    // Output the distance to the target node, which is the weight of the shortest path
    std::cout << distances[v2] << std::endl;
}

// Constructor with parameters
Edge::Edge(double distance, double speedLimit, double adjustment) 
    : d(distance), S(speedLimit), A(adjustment) {

}

// Default constructor definition (I was getting a weird error, something to do with creating an Edge object without any arguments, this fixed it)
Edge::Edge() 
    : d(0.0), S(0.0), A(1.0) { 

}


double Edge::time() const {
    
    if (A == 0) {
        return std::numeric_limits<double>::max();
    }
    return d / (S * A);

}


void Graph::dijkstras_algorithm(int source) {
    // Using priority_queue to store pairs of (distance to source, vertex ID)
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> minHeap;
    
    // Set to keep track of visited nodes
    std::set<int> visited_nodes;

    // Initialize distances to infinity and parents to -1
    distances.clear();
    parents.clear();
    for (const auto& node : graph) {
        distances[node.first] = std::numeric_limits<double>::infinity();
        parents[node.first] = -1;  // Using -1 to indicate no parent
    }

    // distance from source to itself is 0
    distances[source] = 0.0;

    // Start with the source vertex
    minHeap.push({0.0, source});

    while (!minHeap.empty()) {
        auto [current_dist, current_node] = minHeap.top();
        minHeap.pop();

        // If node already visited, skip it
        if (visited_nodes.find(current_node) != visited_nodes.end()) {
            continue;
        }

        visited_nodes.insert(current_node);

        // // Skip processing if a shorter path to this node has already been found
        if (current_dist > distances[current_node]) {
            continue;
        }

        // Check all neighbors of the current node
        for (const auto& edge : graph[current_node]) {
            int neighbor = edge.first;
            double weight = edge.second.time();  // Calculate the weight of the edge
            
            if (weight == std::numeric_limits<double>::max()) {  // Skip blocked paths
                continue;
            }

            double new_dist = distances[current_node] + weight;

            // If the new distance is shorter, update the distance and parent, then add it to pq
            if (new_dist < distances[neighbor] && visited_nodes.find(neighbor) == visited_nodes.end()) {
                distances[neighbor] = new_dist;
                parents[neighbor] = current_node;
                minHeap.push({new_dist, neighbor});
            }
        }
    }
}
