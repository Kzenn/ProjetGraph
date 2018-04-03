#include "Edge.hpp"

/// Overload constructor
Edge::Edge(unsigned int _weight, unsigned int _x, unsigned int _y, bool _direction, const char* _chemin1, const char* _chemin2) : m_weight(_weight), m_x(_x), m_y(_y), m_direction(_direction), im_s1(load_bitmap(_chemin1,NULL)), im_s2(load_bitmap(_chemin2,NULL))
{
    /// Nothing to do here
}

/// Destructor
Edge::~Edge()
{
    /// Nothing to do here !
}

/// Getter to read "m_weight" attribute
unsigned int Edge::getWeight() const
{
    return m_weight;
}

/// Getter to read "m_x" attribute
unsigned int Edge::getX() const
{
    return m_x;
}

/// Getter to read "m_y" attribute
unsigned int Edge::getY() const
{
    return m_y;
}

/// Getter to read "m_direction" attribute
bool Edge::getDirection() const
{
    return m_direction;
}

/// Setter to modify "m_weight" attribute
void Edge::setWeight(unsigned int weight)
{
    m_weight = weight;
}

/// Setter to modify "m_x" attribute
void Edge::setX(unsigned int x)
{
    m_x = x;
}

/// Setter to modify "m_y" attribute
void Edge::setY(unsigned int y)
{
    m_y = y;
}

/// Setter to modify "m_direction" attribute
void Edge::setDirection(bool direction)
{
    m_direction = direction;
}
