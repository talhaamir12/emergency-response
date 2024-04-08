// include libraries here
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "graph.h"


int main(){
    
    // your code goes here...  
    Graph newGraph;
    std::string line;
    std::string command;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        iss >> command; // To detect the command that's inputted

        if (command == "insert") {
            int v1;
            int v2;
            double d;
            double S;

            iss >> v1 >> v2 >> d >> S;

            if (newGraph.insert(v1, v2, d, S)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        } 
        else if (command == "load"){
            std::string filename = line.substr(5);
            int v1;
            int v2;
            double d;
            double S;
            std::ifstream file(filename);
            while (file >> v1 >> v2 >> d >> S) {
                newGraph.insert(v1, v2, d, S);
            }
            file.close();
            std::cout << "success" << std::endl;
        } 
        else if (command == "traffic") {
            int v1;
            int v2;
            double A;
            iss >> v1 >> v2 >> A;
            if (newGraph.traffic(v1, v2, A)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        } 
        else if (command == "update") {
            std::string filename = line.substr(7);
            std::ifstream file(filename);
            int v1;
            int v2;
            double A;
            bool update = false;
            while (file >> v1 >> v2 >> A) {
                if (newGraph.traffic(v1, v2, A)) {
                    update = true;
                }
            }

            if (update) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        }
        else if (command == "print") {
            int v1;
            iss >> v1;
            newGraph.print(v1);
        } 
        else if (command == "delete") {
            int v1;
            iss >> v1;
            if (newGraph.delete_vertex(v1)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        } 
        else if (command == "path") {
            int v1;
            int v2;
            if (!(iss >> v1 >> v2)) {
                std::cout << "failure" << std::endl;
            } else {
                newGraph.path(v1, v2);
            }

        } 
        else if (command == "lowest") {
            int v1;
            int v2;
            if (!(iss >> v1 >> v2)) {
                std::cout << "failure" << std::endl;
            } else {
                newGraph.lowest(v1, v2);
            }

        } 
        else if (command == "exit") {
            break; // Exit out of the loop and end program
        } 
        else {
            std::cout << "Invalid command" << std::endl;
        }
    }
    return 0;
}