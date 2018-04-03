#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED
#include <vector>
#include <set>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include "Edge.hpp"

class Graph
{
    private :
    /// Attributes (members)
    unsigned int m_order = 0; /// Allowed in C++11, number of edges.
    unsigned int m_nb_aretes = 0;
    std::vector<Edge> m_tab; /// Array of edges.
    std::vector<std::vector<int>>TabAretes;

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

    void FileReading(std::string FileName);
};
#endif // GRAPH_HPP_INCLUDED
