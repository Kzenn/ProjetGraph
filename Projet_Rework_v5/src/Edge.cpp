#include "Edge.hpp"

/// Overload constructor
Edge::Edge(Sommet *_a, Sommet *_b,int _weight,  bool _direction) : a(_a), b(_b), m_weight(_weight), m_direction(_direction)
{
    /// Nothing to do here
}

/// Destructor
Edge::~Edge()
{
    /// Nothing to do here !
}

/// Getter to read "m_weight" attribute
int Edge::getWeight()
{
    return m_weight;
}

Sommet& Edge::geta() const
{
    return *a;
}
Sommet& Edge::getb() const
{
    return *b;
}

/// Getter to read "m_direction" attribute
bool Edge::getDirection() const
{
    return m_direction;
}

/// Setter to modify "m_weight" attribute
void Edge::setWeight(int _weight)
{
    m_weight = _weight;
}


/// Setter to modify "m_direction" attribute
void Edge::setDirection(bool direction)
{
    m_direction = direction;
}
