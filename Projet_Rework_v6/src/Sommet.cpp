#include "Sommet.h"

Sommet::Sommet()
{
    //ctor
}

Sommet::Sommet(int _idx, int _pos_x, int _pos_y, BITMAP* _chemin, int _pop, std::string _path) : idx(_idx), pos_x(_pos_x), pos_y(_pos_y), pic(_chemin), pop(_pop), m_chemin(_path)
{
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}

BITMAP* Sommet::getpic()
{
    return pic;
}

int Sommet::getpos_x()
{
    return pos_x;
}
int Sommet::getpos_y()
{
    return pos_y;
}
int Sommet::getidx()
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
std::string Sommet::getchemin()
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

int Sommet::getcolor()
{
    return m_color;
}

void Sommet::setcolor(int c)
{
    m_color = c;
}
