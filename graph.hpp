#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <vector>
#define DEBUG
#ifdef DEBUG
#define LOG(stream) std::cout << "LOG: " << (stream) << std::endl;
#else
#define LOG(stream)
#endif

/** Genetic programming resources */
namespace GP {

};

/** Color representation */
using Color = int;

/** Graph representation using adjacency list */
class Graph {
private:
    int colors_used;
public:
    int size;               ///< |V| - amount of vertices
    std::vector<int> *adj;  ///< Adjacency list
    std::vector<int> *constraint; ///< Vertex color constraints
    Color *colors;          ///< Colors assigned to vertices (set by coloring methods)

    /**
     * Constructor
     * @param size |V| the amount of vertices
     */ 
    Graph(int size);

    /**
     * Constructor loading graph from a file
     * @param graph_file Path to the graph file
     * @param constraint_file Path to file containing constraints or nullptr when there are none
     */ 
    Graph(const char *graph_file, const char *constraint_file=nullptr);

    /** Destructor */
    ~Graph() {
        delete[] adj;
    }

    /**
     * Adds a new edge into the graph
     * @param src 1st vertex this edge connects
     * @param dst 2nd vertex this edge connects
     * @note This method takes the graph as undirected, thus adds edge src -> dst and dst -> src as well.
     */ 
    void add_edge(int src, int dst);
    
    /**
     * Prints the graph to the std::cout
     */ 
    void print();

    /**
     * Creates dot format file containing this graph with coloring bases on colors
     * @param name Graph name
     * @param filename Output dot file path
     */ 
    void create_dot(const char *name, const char *filename=nullptr);

    /**
     * Greedy k coloring algorithm
     * @param k Number of available colors
     * @return true if graph was colored otherwise false
     */ 
    bool kcolor_greedy(int k);
};

#endif//_GRAPH_HPP_