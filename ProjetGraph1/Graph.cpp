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

void Graph::FileReading(std::string FileName)
{
    ///Lire un fichier ligne par ligne
    ///Entrée : le chemin d'accès au fichier
    std::ifstream fichier(FileName, std::ios::in);
    int compteur=0;
    std::string line;



    if(fichier) ///test si le fichier est bien ouvert
    {
        std::cout << "Recuperer donnees => OK" << std::endl;
        while(getline(fichier, line))
        {
            compteur++;
        }
        fichier.close();
        m_nb_aretes=compteur;
    }
        else  ///en cas d'erreur...
    {
        std::cout << "Cannot read " << FileName << std::endl;
    }

    std::vector<int> temp;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    int indic = 0;
    std::string Chaine1;
    std::string Chaine2;
    std::set<int> sommets;
    std::unordered_set<std::string>BitmapA;
    std::vector<std::string>BitmapUtil;

    for(int i=0; i<compteur; i++)
    {
        temp.push_back(4);
        TabAretes.push_back(temp);
    }

    fichier.open(FileName);


    if(fichier) ///test si le fichier est bien ouvert
    {
        while (!fichier.eof())
        {
            fichier >> Chaine1 >> v1 >> v2 >> Chaine2 >>v3;
            std::cout << v1 << " " << v2 << " " << v3 <<std::endl;
            sommets.insert(v1);
            sommets.insert(v2);
            BitmapA.insert(Chaine1);
            BitmapA.insert(Chaine2);
            TabAretes[indic][0]=v1;
            TabAretes[indic][1]=v2;
            TabAretes[indic][2]=v3;
            indic++;

        }

        m_order=sommets.size();
        fichier.close();
        for(const auto& elem : BitmapA)
        {
            BitmapUtil.push_back(elem);
        }
    }
    else  ///en cas d'erreur...
    {
        std::cout << "Cannot read " << FileName << std::endl;
    }
}
