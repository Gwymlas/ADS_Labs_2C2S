#ifndef ADS_LABS_2C2S_GRAPH_H
#define ADS_LABS_2C2S_GRAPH_H
#include <vector>
#include <exception>
#include <iostream>


template<typename T>
class Graph {
    struct Edge {
        T data;
        size_t lenght;

        Edge(T data, size_t lenght): data(data), lenght(lenght) { }
    };

    struct Vertex {
        T data;
        std::vector<Edge> destination;
    };

    std::vector<Vertex> table;

public:

    int get_id(const T& v) const {
        for (int i = 0; i < table.size(); ++i) {
            if(table[i].data == v) return i;
        }
        return -1;
    }


    void add_vertex(const T& source) {
        if (get_id(source) == -1) {
            table.push_back(source);
        }
        else throw std::exception();
    }

    void add_edge(const T& source, const T& destination, size_t lenght) {
        int id_source = get_id(source);
        int id_destination = get_id(destination);
        if ((id_source == -1) || (id_destination == -1)) throw std::exception();
        table[id_source].destination.push_back(Edge(destination, lenght));
    }

    void delete_vertex(const T& vertex) {
        int id_vertex = get_id(vertex);
        if(id_vertex == -1) throw std::exception();
        for (size_t i = 0; i < table.size(); ++i) {
            for (size_t j = 0; j < table[i].destination.size(); ++j) {
                if(table[i].destination[j].data == vertex) table[i].destination.erase(j);
            }
        }
        table.erase(id_vertex);
    }

    void delete_edge(const T& source, const T& destination) {
        int id_source = get_id(source);
        int id_destination = get_id(destination);
        if ((id_source == -1) || (id_destination == -1)) throw std::exception();
        for (size_t i = 0; i < table[id_source].destination.size(); ++i) {
            if (table[id_source].destination[i] == destination) table[id_source].destination.erase(i);
        }
    }

    void print() {
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout<<table[i].data<<std::endl;
            for (size_t j = 0; j < table[i].destination.size(); ++j) {
                std::cout<<table[i].destination[j].data<<"---";
            }
        }
    }
};


#endif //ADS_LABS_2C2S_GRAPH_H
