#ifndef ADS_LABS_2C2S_GRAPH_H
#define ADS_LABS_2C2S_GRAPH_H
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <exception>
#include <iostream>


template<typename TVertex, typename TEdge>
class Graph {

    struct Edge {
        TEdge _data;
        TVertex _dst;

        Edge(const TEdge& data, const TVertex& destination): _data(data), _dst(destination) { }

        Edge(const Edge& rhs) {
            _data = rhs._data;
            _dst = rhs._dst;
        }

    };

    struct Vertex {
        TVertex _data;
        std::list<Edge> _edges;
        bool _colour;


        explicit Vertex(const TVertex& data): _data(data), _colour(false) { }

        Vertex(const Vertex& rhs) {
            _data = rhs._data;
            _edges = rhs._edges;
            _colour = rhs._colour;

        }
    };

    std::vector<Vertex> table;


public:

    int get_id(const TVertex& target) const {
        for (int i = 0; i < table.size(); ++i) {
            if(table[i]._data == target) return i;
        }
        return -1;
    }

    void add_vertex(const TVertex& source) {
        if (get_id(source) == -1) {
            table.push_back(Vertex(source));
        }
        else throw std::exception(); //?
    }

    void add_edge(const TVertex& source, const TVertex& destination, const TEdge& new_edge) {
        int id_source = get_id(source);
        int id_destination = get_id(destination);
        if ((id_source == -1) || (id_destination == -1)) throw std::exception();
        table[id_source]._edges.push_back(Edge(new_edge, destination));
    }

    void delete_vertex(const TVertex& target) {
        int id_vertex = get_id(target);
        if(id_vertex == -1) throw std::exception();
        for (auto it_vertex = table.begin(); it_vertex != table.end(); ) {
            if (it_vertex->_data == target) {
                it_vertex = table.erase(it_vertex);
            }
            else {
                for (auto it_edge = (*it_vertex)._edges.begin();
                     it_edge != (*it_vertex)._edges.end(); ) {
                        if (it_edge->_dst == target) it_edge = (*it_vertex)._edges.erase(it_edge);
                        else ++it_edge;
                }
                ++it_vertex;
            }
        }
    }

    void delete_edge(const TVertex& source, const TVertex& destination) {
        int id_source = get_id(source);
        int id_destination = get_id(destination);
        if ((id_source == -1) || (id_destination == -1)) throw std::exception();
        for (auto it = table[id_source]._edges.begin(); it != table[id_source]._edges.end(); ) {
            if (it->_dst == destination) {
                table[id_source]._edges.erase(it);
                break;
            }
            else ++it;
        }
    }

    void print() {
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout<<table[i]._data;
            for (auto elem = table[i]._edges.begin(); elem != table[i]._edges.end(); ++elem) {
                std::cout<<"---" << elem->_data << " " << elem->_dst;
            }
            std::cout<<std::endl;
        }
    }

    void BFS(const TVertex& from) {
        if (get_id(from) == -1) throw std::exception();
        for(auto elem: table) {
            elem._colour = false;
            //elem._prev = nullptr;
        }
        std::queue<Vertex> q;
        Vertex s = table[get_id(from)];
        q.push(s);
        s._colour = true;
        while(!q.empty()) {
            Vertex u = q.front();
            q.pop();
            for(auto elem: u._edges) {
                Vertex& v = table[get_id(elem._dst)];
                if (v._colour == false) {
                    v._colour = true;
                    //v._prev = u._data;
                    q.push(v);
                }
            }
            std::cout << u._data << std::endl;
        }
    }

    std::pair<std::list<TVertex>, double> bellman_ford_algorithm(const TVertex& src, const TVertex& dst) {
//        std::map<TVertex, std::pair<double, TVertex>> distance;
//        distance[src] = std::make_pair(0, src);
//        for (auto elem: table) {
//            if (src == elem._data) continue;
//            distance[elem] = std::make_pair(std::numeric_limits<double>::max(), elem);
//        }
        std::vector<double> distance(table.size(), std::numeric_limits<double>::max());
        distance[get_id(src)] = 0;

        for (size_t i = 0; i + 1 < table.size(); ++i) {
            for(size_t j = 0; j < table.size(); ++j) {
                for (auto elem: table[j]._edges) {
                    int id_dst = get_id(elem._dst);
                    if (distance[id_dst] > distance[j] + static_cast<double>(elem)) {
                        distance[id_dst] = distance[j] + static_cast<double>(elem);
                    }
                }
            }
        }

        for(size_t j = 0; j < table.size(); ++j) {
            for (auto elem: table[j]._edges) {
                int id_dst = get_id(elem._dst);
                if (distance[id_dst] > distance[j] + static_cast<double>(elem)) throw std::exception();
            }
        }
        
    }

};


#endif //ADS_LABS_2C2S_GRAPH_H
