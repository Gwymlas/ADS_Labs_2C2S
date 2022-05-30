#include <iostream>
#include "Graph.h"
#include <string>

int main() {
    Graph<std::string, double> g;
    g.add_vertex("Samara");
    g.add_vertex("Moscow");
    g.add_vertex("Piter");
    g.add_vertex("Orenburg");
    g.add_vertex("Syzran");
    g.add_vertex("TLT");
    g.add_vertex("Kirov");
    g.add_edge("Samara", "Piter", 10);
    g.add_edge("Samara", "Moscow", 6);
    g.add_edge("Moscow", "Piter", 2);
    g.add_edge("Samara", "Orenburg", 11);
    g.add_edge("Piter", "Orenburg", 22);
    g.add_edge("Piter", "Syzran", 224);
    g.add_edge("Piter", "TLT", 242);
    g.add_edge("Piter", "Kirov", 232);
    auto result = g.bellman_ford_algorithm("Samara", "Kirov");
    std::cout << "Кратчайший путь: " << std::endl;
    for (auto elem: result.first) {
        std::cout << elem << "->";
    }
    std::cout << result.second << std::endl;
    std::cout << "------------------" << std::endl;
    g.print();
    std::cout << "------------------" << std::endl;
    g.BFS("Piter");
    g.delete_edge("Samara", "Piter");
    //g.print();
    g.delete_vertex("Moscow");
    //g.print();

    return 0;
}