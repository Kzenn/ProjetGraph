#include "Sommet.h"

Sommet::Sommet()
{
    //ctor
}

Sommet::Sommet(unsigned int _idx, unsigned int _pos_x, unsigned int _pos_y, BITMAP* _chemin, unsigned int _pop, std::string _path) : idx(_idx), pos_x(_pos_x), pos_y(_pos_y), pic(_chemin), pop(_pop), m_chemin(_path)
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}

BITMAP* Sommet::getpic() const
{
    return pic;
}

int Sommet::getpos_x() const
{
    return pos_x;
}
int Sommet::getpos_y() const
{
    return pos_y;
}
unsigned int Sommet::getidx() const
{
    return idx;
}

void Sommet::setidx(int _idx)
{
    idx = _idx;
}

void Sommet::setpos_x(int x)
{
    pos_x = x;
}
void Sommet::setpos_y(int y)
{
    pos_y = y;
}
std::string Sommet::getchemin() const
{
    return m_chemin;
}
int Sommet::getpop()
{
    return pop;
}

void Sommet::setpop(int p)
{
    pop=p;
}
