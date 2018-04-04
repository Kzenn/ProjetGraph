#include "Graph.hpp"

/// Overload constructor
Graph::Graph(unsigned int _order) : m_order(_order)
{
    /// Nothing to do here
}

/// Destructor
Graph::~Graph()
{
    /// Nothing to do here !
}

/// Getter to read "m_order" attribute
unsigned int Graph::getOrder() const
{
    return m_order;
}

/// Getter to read "m_tab" attribute
std::vector<Edge>& Graph::getTab()
{
    return m_tab;
}

/// Setter to modify "m_order" attribute
void Graph::setOrder(unsigned int order)
{
    m_order = order;
}
