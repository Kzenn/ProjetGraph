#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED
#include <vector>
#include "Edge.hpp"

class Graph
{
    friend class Edge;
    friend class Sommet;

private :
    /// Attributes (members)
    unsigned int m_order = 0; /// Allowed in C++11, number of edges.
    std::vector<Edge> m_tab; /// Array of edges.

public :
    /// Constructors and destructor
    Graph(unsigned int _order);
    ~Graph();

    /// Getters
    unsigned int getOrder() const;
    std::vector<Edge>& getTab();

    /// Setters
    void setOrder(unsigned int order);

    /// Methods (functions and procedures)
};
#endif // GRAPH_HPP_INCLUDED
