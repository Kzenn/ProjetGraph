#ifndef SOMMET_H
#define SOMMET_H
#include <allegro.h>
#include <iostream>
#include <string>

class Sommet
{
    friend class Edge;
    friend class Graph;

public:
    Sommet();
    Sommet(int _idx, int _pos_x, int _pos_y, BITMAP* _chemin,int _pop, std::string _path);
    virtual ~Sommet();

    BITMAP* getpic();
    int getpos_x();
    int getpos_y();
    void setpos_x(int x);
    void setpos_y(int y);
    void setpop(int p);
    int getidx();
    void setidx(int _idx);
    int getpop();
    std::string getchemin() ;

    int getcolor();
    void setcolor(int c);

protected:

private:
    std::string m_chemin;
    BITMAP* pic;
    unsigned int idx = 0;
    int pos_x = 0;
    int pos_y = 0;
    int pop =0;
    int m_color=-1;
};

#endif // SOMMET_H
