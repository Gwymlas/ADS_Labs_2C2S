#include <iostream>
#include "Graph.h"
#include <string>

int main() {
    auto Samara = Town("Samara", 1100);
    auto Moscow = Town("Moscow", 15000);
    auto Piter = Town("Piter", 8000);
    auto Orenburg = Town("Orenburg", 800);
    auto Syzran = Town("Syzran", 180);
    auto TLT = Town("TLT", 700);
    auto Kirov = Town("Kirov", 900);

    auto Samara_Piter = Road("M1", federal, 20, 1.2 );
    auto Samara_Moscow = Road("M2", federal, 10, 1.3 );
    auto Moscow_Piter = Road("M3", federal, 12, 0 );
    auto Samara_Orenburg = Road("M4", federal, 9, 0 );
    auto Piter_Orenburg = Road("M5", federal, 7, 0 );
    auto Piter_Syzran = Road("M6", federal, 45, 1 );
    auto Piter_TLT = Road("M7", federal, 22, 0 );
    auto Piter_Kirov = Road("M8", federal, 11, 0 );

    Graph<Town, Road> g;

    g.add_vertex(Samara);
    g.add_vertex(Moscow);
    g.add_vertex(Piter);
    g.add_vertex(Orenburg);
    g.add_vertex(Syzran);
    g.add_vertex(TLT);
    g.add_vertex(Kirov);
    g.add_edge(Samara, Piter, Samara_Piter);
    g.add_edge(Samara, Moscow, Samara_Moscow);
    g.add_edge(Moscow, Piter, Moscow_Piter);
    g.add_edge(Samara, Orenburg,Samara_Orenburg);
    g.add_edge(Piter, Orenburg, Piter_Orenburg);
    g.add_edge(Piter, Syzran, Piter_Syzran);
    g.add_edge(Piter, TLT, Piter_TLT);
    g.add_edge(Piter, Kirov, Piter_Kirov);

    g.print();
    auto result = g.bellman_ford_algorithm(Samara, Kirov);
    std::cout << "Кратчайший путь: " << std::endl;
    for (const auto& elem: result.first) {
        elem.print_town();
        std::cout << "->" << std::endl;
    }
    std::cout << "Итоговый вес пути: " << result.second << std::endl;

//    g.delete_vertex(Moscow);
//    g.print();
//    result = g.bellman_ford_algorithm(Samara, Kirov);
//    std::cout << "Кратчайший путь: " << std::endl;
//    for (const auto& elem: result.first) {
//        elem.print_town();
//        std::cout << "->";
//    }
//    std::cout << result.second << std::endl;

    std::cout << "\n" <<"Обход в ширину" << std::endl;
    g.BFS(Piter);



    return 0;
}