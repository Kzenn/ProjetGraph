#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED
#include <vector>
#include <allegro.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Edge.hpp"
#include "Sommet.h"


class Graph
{
    friend class Edge;
    friend class Sommet;

private :
    /// Attributes (members)
    int m_order = 0; /// Allowed in C++11, number of edges.
    std::vector<Edge> EdgeTab; /// Array of edges.
    std::vector<Sommet*> vecSommet;    ///Vector of Sommet*
    std::vector<std::string> GraphFile;  ///Vector of files' string
    std::vector<std::vector<int>> AdjMatrixSucc; ///Matrice successeur

    ///ALGO FORTE CONNEXITE
    std::vector<int>_alpha;
    std::vector<int> m_beta;
    int m_size_alpha;
    int m_size_beta;
    std::vector<int> m_tab_composantes;

public :
    /// Constructors and destructor
    Graph();
    ~Graph();

    /// Getters
    unsigned int getOrder();
    std::vector<Edge>& getEdgeTab();
    std::vector<Sommet*>& getSommetTab();
    std::vector<std::string>& getGraphFile();
    std::vector<int> getTabComposante();

    /// Setters
    void setOrder(unsigned int order);

    /// Methods (functions and procedures)
    void FillVecSommet(Sommet* s);
    void ReadFile(std::string FileName);
    void SaveFile(std::string FileName);
    void ReadFileDocument();
    void WriteFileDocument(std::string nom);
    std::string CreateFile();

    void ClearVecSommet();
    void ClearVecEdge();
    void ClearVecFileName();

    void AddVertex();
    void AddEdge(Sommet* s1, Sommet* s2);

    void DeleteVertex(Sommet *s);
    void DeleteEdge(Sommet* s1, Sommet* s2);

    void BuildAdjMatrix();
    std::vector<std::vector<int>> getAdjMatrix();

    ///FORTE CONNEXITE
    void Malgrange();
    void Affiche_composantes_FC(BITMAP* buffer);
    void Affiche_Mat();
    std::vector<std::vector<int>> Produit_matriciel(std::vector<std::vector<int>>A,std::vector<std::vector<int>>B,int s);
};

struct Comp
{
    bool operator()(Sommet*s1, Sommet* s2)
    {
        return s1->getidx() < s2->getidx();

    }
};
#endif // GRAPH_HPP_INCLUDED
