//
// Created by Andrii Zhupanov on 27.12.2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <time.h>
#include <algorithm>
#include "UnionFind.h"
#include "DynamicTable.h"
#include "Helpers.h"

class Graph {
private:
    int numNodes;
    int numEdges;
    DynamicTable<Node> nodes;
    DynamicTable<Edge> edges;

public:
    Graph(int n = 0) : numNodes(n), numEdges(0) {}

    void addNode(double x, double y) {
       nodes.append(Node(x, y));
    }

    void addEdge(int src, int dest, double weight) {
        edges.append(Edge(src, dest, weight));
        numEdges++;
    }

    DynamicTable<Edge> kruskalMST(bool useRank = true, bool usePathCompression = true) {
        DynamicTable<Edge> result;
        UnionFind uf(numNodes);

        clock_t start = clock();
        std::sort(edges.begin(), edges.end());
        clock_t sortEnd = clock();

        double totalWeight = 0;
        uf.resetFindCount();

        for(const Edge& edge : edges) {
            int srcRoot = usePathCompression ? uf.findPC(edge.src) : uf.find(edge.src);
            int destRoot = usePathCompression ? uf.findPC(edge.dest) : uf.find(edge.dest);

            if(srcRoot != destRoot) {
                result.append(edge);
                totalWeight += edge.weight;

                if(useRank) {
                    uf.unionByRank(edge.src, edge.dest);
                } else {
                    uf.unionSets(edge.src, edge.dest);
                }
            }
        }

        clock_t end = clock();

        std::cout << "MST Results:\n";
        std::cout << "Number of edges in MST: " << result.get_size() << "\n";
        std::cout << "Total weight of MST: " << totalWeight << "\n";
        std::cout << "Sort time: " << (double)(sortEnd - start) / CLOCKS_PER_SEC * 1000 << " ms\n";
        std::cout << "Main loop time: " << (double)(end - sortEnd) / CLOCKS_PER_SEC * 1000 << " ms\n";
        std::cout << "Number of find operations: " << uf.getFindCount() << "\n\n";

        return result;
    }

    static Graph loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if(!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        int n;
        file >> n;
        Graph graph(n);

        for(int i = 0; i < n; i++) {
            double x, y;
            file >> x >> y;
            graph.addNode(x, y);
        }

        int e;
        file >> e;
        for(int i = 0; i < e; i++) {
            int src, dest;
            double weight;
            file >> src >> dest >> weight;
            graph.addEdge(src, dest, weight);
        }
        std::cout << e << std::endl;
        return graph;
    }

    void generateDotFile(const std::string& filename, const DynamicTable<Edge>& highlightEdges = DynamicTable<Edge>()) const {
        std::ofstream dotFile(filename);
        dotFile << "graph G {\n";
        dotFile << "    node [shape=circle];\n";

        for (int i = 0; i < numNodes; i++) {
            const Node& node = nodes.find(i);
            dotFile << "    " << i << " [pos=\"" << node.x * 2000 << "," << node.y * 2000 << "!\"];\n";
        }

        auto isInMST = [&highlightEdges](const Edge& edge) {
            for (const Edge& mstEdge : highlightEdges) {
                if ((mstEdge.src == edge.src && mstEdge.dest == edge.dest) ||
                    (mstEdge.src == edge.dest && mstEdge.dest == edge.src)) {
                    return true;
                }
            }
            return false;
        };

        for (const Edge& edge : edges) {
            dotFile << "    " << edge.src << " -- " << edge.dest
                   << " [label=\"" << edge.weight << "\"";

            if (isInMST(edge)) {
                dotFile << ", color=red, penwidth=2.0";
            }

            dotFile << "];\n";
        }

        dotFile << "}\n";
        dotFile.close();

        std::string pngFilename = filename.substr(0, filename.find_last_of('.')) + ".png";
        std::string command = "dot -Kneato -n -Tpng -Gsize=10,10! -Gdpi=300 " + filename + " -o " + pngFilename;
        system(command.c_str());
    }
};

#endif //GRAPH_H
