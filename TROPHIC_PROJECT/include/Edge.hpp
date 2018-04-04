#ifndef EDGE_HPP_INCLUDED
#define EDGE_HPP_INCLUDED
#include <allegro.h>

class Edge
{
    friend class Graph;
    friend class Sommet;

private :
    /// Attributes (members)
    unsigned int m_weight = 0; /// Allowed in C++11, weight of an edge.
    unsigned int m_x = 0; /// Allowed in C++11, left extremity of an edge.
    unsigned int m_y = 0; /// Allowed in C++11, right extremity of an edge.
    bool m_direction = false; /// Allowed in C++11, direction of an edge.
    BITMAP* im_s1 = NULL;
    BITMAP* im_s2 = NULL;

public :
    /// Constructors and destructor
    Edge(unsigned int _weight, unsigned int _x, unsigned int _y, bool _direction, const char* _chemin1, const char* _chemin2);
    ~Edge();

    /// Getters
    unsigned int getWeight() const;
    unsigned int getX() const;
    unsigned int getY() const;
    bool getDirection() const;

    /// Setters
    void setWeight(unsigned int weight);
    void setX(unsigned int x);
    void setY(unsigned int y);
    void setDirection(bool direction);

    /// Methods (functions and procedures)
};
#endif // EDGE_HPP_INCLUDED
