//
// Created by Andrii Zhupanov on 27.12.2024.
//

#include <fstream>
#include <string>
#include <iostream>
#include "Graph.h"

int main() {
    try {
        for(int i = 1; i < 4; ++i) {
            std::string filename = "../g" + std::to_string(i) + ".txt";
            Graph g = Graph::loadFromFile(filename);

            std::cout << "For " << filename << std::endl;
            std::cout << "Using union by rank and path compression:\n";
            auto mst = g.kruskalMST(true, true);

            std::cout << "Using simple union and find:\n";
            g.kruskalMST(false, false);

            std::cout << "Using union by rank without path compression:\n";
            g.kruskalMST(true, false);

            std::cout << "Using simple union with path compression:\n";
            g.kruskalMST(false, true);

            if(i == 1) {
                g.generateDotFile("graph_with_mst.dot", mst);
            }
        }


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}