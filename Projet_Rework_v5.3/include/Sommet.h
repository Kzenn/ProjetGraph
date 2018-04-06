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
    Sommet(unsigned int _idx, unsigned int _pos_x, unsigned int _pos_y, BITMAP* _chemin, unsigned int _pop, std::string _path);
    virtual ~Sommet();

    BITMAP* getpic() const;
    int getpos_x() const;
    int getpos_y() const;
    void setpos_x(int x);
    void setpos_y(int y);
    void setpop(int p);
    unsigned int getidx() const;
    void setidx(int _idx);
    int getpop();
    std::string getchemin() const;

protected:

private:
    std::string m_chemin;
    BITMAP* pic;
    unsigned int idx = 0;
    int pos_x = 0;
    int pos_y = 0;
    int pop =0;
};

#endif // SOMMET_H
