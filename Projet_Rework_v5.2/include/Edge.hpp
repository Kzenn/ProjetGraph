#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED
#include <allegro.h>
#include "Sommet.h"

class Edge
{
    friend class Graph;
    friend class Sommet;

private :
    /// Attributes (members)*
    Sommet *a;
    Sommet *b;
    int m_weight = 0; /// Allowed in C++11, weight of an edge.
    bool m_direction = false; /// Allowed in C++11, direction of an edge.

public :
    /// Constructors and destructor
    Edge(Sommet *_a, Sommet *_b, int _weight, bool _direction);
    ~Edge();

    /// Getters
    int getWeight();
    bool getDirection() const;
    Sommet &geta() const;
    Sommet &getb() const;

    /// Setters
    void setWeight(int _weight);
    void setDirection(bool direction);

    /// Methods (functions and procedures)
};
#endif // EDGE_HPP_INCLUDED
