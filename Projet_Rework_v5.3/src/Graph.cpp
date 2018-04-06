#include "Graph.hpp"
#define SCREEN_H 768
#define SCREEN_W 1024

#define TAILLEX 100
#define TAILLEY 100

/// Overload constructor
Graph::Graph()
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

/// Getter to read "EdgeTab" attribute
std::vector<Edge>& Graph::getEdgeTab()
{
    return EdgeTab;
}

/// Setter to modify "m_order" attribute
void Graph::setOrder(unsigned int order)
{
    m_order = order;
}

std::vector<Sommet*>& Graph::getSommetTab()
{
    return vecSommet;
}

std::vector<std::string>& Graph::getGraphFile()
{
    return GraphFile;
}

void Graph::FillVecSommet(Sommet* s)
{
    vecSommet.push_back(s);
}

void Graph::ClearVecSommet()
{
    vecSommet.clear();
}

void Graph::ClearVecEdge()
{
    EdgeTab.clear();
}

void Graph::ClearVecFileName()
{
    GraphFile.clear();
}


void Graph::ReadFile(std::string FileName)
{
    ///Lire un fichier ligne par ligne
    ///Entrée : le chemin d'accès au fichier
    std::string chemin = "Donnees/";
    std::string FName = chemin+FileName;
    std::ifstream fichier(FName, std::ios::in);


    std::vector<int> temp;
    int num1 = 0;
    int num2 = 0;
    int num1_m = 999;
    int num2_m = 999;
    int poids = 0;
    int num_a =0;
    int x1 =0;
    int x2 = 0;
    int y1 =0;
    int y2 = 0;
    int population = 0;
    int population2 = 0;
    Sommet* temporaire;
    bool check=true;
    bool check2=true;


    Sommet* tri;
    int mem=0;
    std::string Chaine1;
    std::string Chaine2;
    ClearVecEdge();
    ClearVecSommet();


    if(fichier) ///test si le fichier est bien ouvert
    {
        while(!fichier.eof())
        {
            check=true;
            check2=true;
            BITMAP *pic = nullptr;
            BITMAP *pic2 = nullptr;

            fichier >> num_a >> Chaine1 >> num1 >> num2 >> Chaine2 >>poids >> x1 >> y1 >> x2 >> y2 >> population >> population2;
            std::cout << "LU ====  " << num_a << "   " << Chaine1 << "   " << num1 << "   "<<  num2 << "   " <<  Chaine2 << "   " << poids << "  " <<  x1 << "   " << y1 << "   " <<  x2 << "   " << y2 << "  " <<  population <<  "  " <<  population2 << std::endl;
            if(x1<88)
                x1 = 88;
            if(x1+TAILLEX>SCREEN_W)
                x1 = SCREEN_W-TAILLEX;
            if(y1+TAILLEY>SCREEN_H)
                y1 = SCREEN_H-TAILLEY;
            if(y1<0)
                y1 = 0;
            if(x2<88)
                x2 = 88;
            if(x2+TAILLEX>SCREEN_W)
                x2 = SCREEN_W-TAILLEX;
            if(y2+TAILLEY>SCREEN_H)
                y2 = SCREEN_H-TAILLEY;
            if(y2<0)
                y2 = 0;
            pic = load_bitmap(Chaine1.c_str(), NULL);
            pic2 = load_bitmap(Chaine2.c_str(), NULL);
            Sommet *vi = new Sommet(num1,x1,y1,pic, population, Chaine1);
            Sommet *vi2 = new Sommet(num2,x2,y2,pic2, population2, Chaine2);
            Edge *ve = new Edge(vi,vi2,poids,false);


            if(num1_m==999 && num2_m==999)
            {
                EdgeTab.push_back(*ve);
                std::cout << "ve dans edge : " << ve->a->getchemin() << " et " << ve->b->getchemin() << std::endl;
            }
            else
            {
                if(num1_m!=num1 || num2_m!=num2)
                {
                    std::cout << "ELSE" << std::endl;
                    EdgeTab.push_back(*ve);
                    std::cout << "ve dans edge : " << ve->a->getchemin() << " et " << ve->b->getchemin() << std::endl;
                }
            }




            if(vecSommet.size()!=0)
            {
                for(int i=0; i<vecSommet.size(); i++)
                {
                    //std::cout << "TOUR DE BOUCLE : " << i << std::endl;
                    //std::cout << "VI : " << vi->getidx() << std::endl;
                    //std::cout << "VI2 : " << vi2->getidx() << std::endl;
                    //std::cout << "i : " << vecSommet[i]->getidx() << std::endl;
                    if(vi->getidx()==vecSommet[i]->getidx())
                    {
                        check=false;
                    }
                    if(vi2->getidx()==vecSommet[i]->getidx())
                    {
                        check2=false;
                    }

                    // std::cout << std::endl;
                }
                if(check==true)
                {
                    // std::cout << "AJOUT : " << vi->getchemin() << std::endl;
                    vecSommet.push_back(vi);
                }
                if(check2==true)
                {
                    // std::cout << "AJOUT : " << vi2->getchemin() << std::endl;
                    vecSommet.push_back(vi2);
                }
            }
            else
            {
                //std::cout << "ELSE VI : " << vi->getidx() << std::endl;
                // std::cout << "ELSE VI2 : " << vi2->getidx() << std::endl;
                vecSommet.push_back(vi);
                vecSommet.push_back(vi2);
            }

            num1_m = num1;
            num2_m = num2;
        }

        std::cout << std::endl;
        std::cout << "LOOOOOOOOOL" << std::endl;


        /*for(int i=0; i<vecSommet.size(); i++)
        {
            if(i+1<vecSommet.size())
            {
                if(vecSommet[i]->getidx()>vecSommet[i+1]->getidx())
                {
                    temporaire = vecSommet[i];
                    vecSommet[i] = vecSommet[i+1];
                    vecSommet[i+1] = temporaire;
                }
            }
        }*/
        std::sort(vecSommet.begin(), vecSommet.begin()+vecSommet.size(),Comp());


        for(int i=0; i<vecSommet.size(); i++)
        {
            std::cout << vecSommet[i]->getidx() << "  " << vecSommet[i]->getchemin() << std::endl;
        }
        for(int i=0; i<EdgeTab.size(); i++)
        {
            std::cout <<EdgeTab[i].a->getidx() << " " << EdgeTab[i].b->getidx() << " " << EdgeTab[i].a->getchemin() << "  " << EdgeTab[i].b->getchemin() << std::endl;
        }



        fichier.close();
        std::cout << "EDGE TAB SIZE : " << EdgeTab.size() << std::endl;
        std::cout << "VEC TAB SIZE : " << vecSommet.size() << std::endl;
    }

    else  ///en cas d'erreur...
    {
        std::cout << "Cannot read " << FileName << std::endl;
    }
}

void Graph::SaveFile(std::string FileName)
{
    std::cout << "REEEEEEEEEEECRITURE" << std::endl;
    int idx = 0;
    std::string chemin = "Donnees/";
    std::string FName = chemin+FileName;
    std::ofstream fichier(FName, std::ios::out | std::ios::trunc);
    if(fichier)
    {
        for(int i = 0 ; i<EdgeTab.size(); i++)
        {
            fichier << idx << " " << EdgeTab[i].a->m_chemin << " " << EdgeTab[i].a->idx << " " << EdgeTab[i].b->idx << " "
                    << EdgeTab[i].b->m_chemin << " " << EdgeTab[i].m_weight << " " << EdgeTab[i].a->pos_x << " " << EdgeTab[i].a->pos_y << " "
                    << EdgeTab[i].b->pos_x << " " << EdgeTab[i].b->pos_y << " " <<EdgeTab[i].a->pop << " " << EdgeTab[i].b->pop << std::endl;
            idx++;
        }
    }

}

void Graph::ReadFileDocument()
{
    ///Lire un fichier ligne par ligne
    ///Entrée : le chemin d'accès au fichier
    std::string FileName = "Fichiers.txt";
    std::ifstream fichier(FileName, std::ios::in);

    std::string nom;


    if(fichier) ///test si le fichier est bien ouvert
    {
        while (!fichier.eof())
        {
            fichier >> nom;
            GraphFile.push_back(nom);
        }

        fichier.close();
    }

    else  ///en cas d'erreur...
    {
        std::cout << "Cannot read " << FileName << std::endl;
    }
}


void Graph::AddVertex()
{
    allegro_message("Entrer les parametres de votre sommet");
    int num1 = vecSommet.size();
    int x1 = 0;
    int y1 = 0;
    int population = 0;
    std::string Chaine1;
    BITMAP *pic = nullptr;

    std::cout << " veuillez saisir la position en x du sommet : " << std::endl;
    std::cin >> x1;

    if(x1<88)
    {
        x1 = 88;
        std::cout << " valeur incorrect nous avons change votre valeur en x = " << x1 << std::endl;
    }

    if(x1+TAILLEX>SCREEN_W)
    {
        x1 = SCREEN_W-TAILLEX;
        std::cout << " valeur incorrect nous avons change votre valeur en x = " << x1 << std::endl;
    }

    std::cout << " veuillez saisir la position en y du sommet : " << std::endl;
    std::cin >> y1;

    if(y1+TAILLEY>SCREEN_H)
    {
        y1 = SCREEN_H-TAILLEY;
        std::cout << " valeur incorrect nous avons change votre valeur en y = " << y1 << std::endl;

    }

    if(y1<0)
    {
        y1 = 0;
        std::cout << " valeur incorrect nous avons change votre valeur en y = " << y1 << std::endl;
    }

    std::cout << " veuillez saisir la population de votre nouveau sommet : " << std::endl;
    std::cin >> population;
    if(population <= 0 )
    {
        population = 0;
        std::cout << " valeur incorrect nous avons change votre valeur en = " << population << std::endl;
    }

    std::cout << " veuillez saisir le chemin d'acces de l image : " << std::endl;
    std::cin >> Chaine1;

    pic = load_bitmap(Chaine1.c_str(), NULL);

    Sommet *vi = new Sommet(num1,x1,y1,pic, population, Chaine1);
    vecSommet.push_back(vi);
    allegro_message("Votre sommet est ajoute");
}

void Graph::AddEdge(Sommet* s1, Sommet* s2)
{
    bool existant = false;
    for(int j = 0 ; j<EdgeTab.size(); j++)
    {
        if(EdgeTab[j].geta().getchemin()==s1->getchemin() && EdgeTab[j].getb().getchemin()==s2->getchemin())
        {
            existant = true;
        }
        else if(EdgeTab[j].geta().getchemin()==s2->getchemin() && EdgeTab[j].getb().getchemin()==s1->getchemin())
        {
            existant = true;
        }

    }
    if(existant==false)
    {
        Edge *ve = new Edge(s1,s2,5,false);
        EdgeTab.push_back(*ve);
    }
}


void Graph::DeleteVertex(Sommet* s)
{
    std::vector<int>erase_v;
    rest(200);
    vecSommet.erase(vecSommet.begin()+s->getidx());
    std::cout << "  EFFACE   : " <<s->getchemin() << std::endl;

    ///ON CHERCHE LES LIGNES A EFFACER
    for(int j = 0 ; j<EdgeTab.size(); j++)
    {
        if(EdgeTab[j].geta().getchemin() == s->getchemin())
        {
            erase_v.push_back(j);
        }
        else if(EdgeTab[j].getb().getchemin() == s->getchemin())
        {
            erase_v.push_back(j);
        }
    }
    ///ERASE DANS TABLEAU
    for(int j = 0 ; j<erase_v.size(); j++)
    {
        std::cout << "ON EFFACE DANS TABLEAU : " << EdgeTab[erase_v[j]].geta().getchemin() << "  ET     " << EdgeTab[erase_v[j]].getb().getchemin() << std::endl;
    }
    ///ERASE DANS TABLEAU
    for(int j = 0 ; j<erase_v.size(); j++)
    {
        erase_v[j]-=j;
        EdgeTab.erase(EdgeTab.begin()+erase_v[j]);
    }
    erase_v.clear();

    std::cout << "\n\nAPRES EFFACEMENT WESH" << std::endl;
    for(int i=0; i<EdgeTab.size(); i++)
    {
        std::cout <<EdgeTab[i].a->getidx() << " " << EdgeTab[i].b->getidx() << " " << EdgeTab[i].a->getchemin() << "  " << EdgeTab[i].b->getchemin() << std::endl;
    }

    ///CHANGE INDICE DANS VECSOMMET
    std::cout << "SIZE : " << vecSommet.size() << std::endl;
    for(int j = 0 ; j<vecSommet.size(); j++)
    {
        if(vecSommet[j]->getidx()>s->getidx())
        {
            std::cout << "ICI POUR " << s->getidx() <<" ON A      "<< vecSommet[j]->getidx()-1 <<std::endl;
            vecSommet[j]->setidx(vecSommet[j]->getidx()-1);
            std::cout << "PREUVE :" <<  vecSommet[j]->getidx() << "     AVEC SOMMET     " << vecSommet[j]->getchemin()<< std::endl;
        }
    }

    for(int j = 0 ; j<EdgeTab.size(); j++)
    {
        for(int p = 0 ; p<vecSommet.size(); p++)
        {
            std::cout << "CRASH" << std::endl;
            if(EdgeTab[j].geta().getchemin()==vecSommet[p]->getchemin())
            {
                EdgeTab[j].geta().setidx(vecSommet[p]->getidx());
            }
            if(EdgeTab[j].getb().getchemin()==vecSommet[p]->getchemin())
            {
                EdgeTab[j].getb().setidx(vecSommet[p]->getidx());
            }
        }
    }



    std::cout << "APRES EFFACEMENT :" << std::endl;
    for(int i=0; i<vecSommet.size(); i++)
    {
        std::cout << vecSommet[i]->getidx() << " a pour nom " << vecSommet[i]->getchemin() << std::endl;
    }
    for(int i=0; i<EdgeTab.size(); i++)
    {
        std::cout <<EdgeTab[i].a->getidx() << " " << EdgeTab[i].b->getidx() << " " << EdgeTab[i].a->getchemin() << "  " << EdgeTab[i].b->getchemin() << std::endl;
    }

}


void Graph::DeleteEdge(Sommet* s1, Sommet* s2)
{
    for(int j = 0 ; j<EdgeTab.size(); j++)
    {
        if(EdgeTab[j].geta().getchemin()==s1->getchemin() && EdgeTab[j].getb().getchemin()==s2->getchemin())
        {
            EdgeTab.erase(EdgeTab.begin()+j);
        }
        else if(EdgeTab[j].geta().getchemin()==s2->getchemin() && EdgeTab[j].getb().getchemin()==s1->getchemin())
        {
            EdgeTab.erase(EdgeTab.begin()+j);
        }

    }
}
void Graph::WriteFileDocument(std::string nom)
{
    std::ofstream fichier("Fichiers.txt", std::ios::app);
    std::string line;
    if(fichier) ///test si le fichier est bien ouvert
    {
        fichier << nom;
        fichier.close();

    }
    else  ///en cas d'erreur...
    {
        std::cout << "Cannot read Fichiers.txt" << std::endl;
    }

}

std::string Graph::CreateFile()
{
    std::string FileName;
    std::string chemin;
    std::cout << "choisir un nom de fichier ou stocker les donnees du graphe: " << std::endl;
    allegro_message("choisir un nom de fichier ou stocker les donnees du graphe.");
    std::cin >> chemin;
    std::string fic = "Donnees/";
    FileName = fic + chemin;
    std::ofstream fichier(FileName, std::ios::app);

    if(fichier) ///test si le fichier est bien ouvert
    {
        std::cout << "Fichier bien cree ! " << std::endl;
        WriteFileDocument(chemin);
        fichier.close();

    }

    else  ///en cas d'erreur...
    {
        std::cout << "Cannot read " << FileName << std::endl;
    }
    return chemin;

}

std::vector<int> Graph::uneComposanteFortementConnexe (std::vector<std::vector<int>> adjacence, int ordre, int s)
{
    //Variables locales
    std::vector<int> c1;
    std::vector<int> c2 ; // composantes connexes directes partant de s et indirectes arrivant vers s
    std::vector<int> c ; // composante fortement connexe = c1  c2 à retourner
    std::vector<int> marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y ; // numéros de sommets intermédiaires des composantes connexes
    int ajoute = 1 ; // booléen indiquant si une nouvelle composante connexe est ajoutée

    // Allouer les tableaux dynamiques c1, c2, c et marques de taille « ordre »
    c1.resize(ordre);
    c2.resize(ordre);
    c.resize(ordre);
    marques.resize(ordre);

    // Initialiser les valeurs de ces tableaux à 0

    for (int i = 0 ; i < ordre ; i++)
    {
        c1[i] = 0;
        c2[i] = 0;
        c[i] = 0;
        marques[i] = 0;
    }
    // Rendre le sommet s connexe
    c1[s] = 1 ;
    c2[s] = 1 ;
    // Recherche des composantes connexes partant de s à ajouter dans c1 :
    while (ajoute)
    {
        ajoute = 0; // à chaque tour, recherche d’une nouvelle composante connexe à ajouter
        // Pour tous les sommets x non marqués et connectés en partant de s
        // Marquer chaque sommet x et connecter les sommets non marqués y adjacents à x
        for (x=0 ; x<ordre ; x++)
        {
            if (!marques[x] && c1[x])
            {
                marques[x] = 1 ;
                for (y=0 ; y<ordre ; y++)
                {
                    if (adjacence[x][y] && !marques[y])
                    {
                        c1[y] = 1 ;
                        ajoute = 1 ; // nouvelle composante connexe ajoutée
                    }
                }
            }
        }
        // Recherche des composantes connexes arrivant à s à ajouter dans c2 :
        while (ajoute)
        {
            ajoute = 0; // à chaque tour, recherche d’une nouvelle composante connexe à ajouter
            // Pour tous les sommets x non marqués et connectés en partant de s
            // Marquer chaque sommet x et connecter les sommets non marqués y adjacents à x
            for (x=0 ; x<ordre ; x++)
            {
                if (!marques[x] && c2[x])
                {
                    marques[x] = 1 ;
                    for (y=0 ; y<ordre ; y++)
                    {
                        if (adjacence[x][y] && !marques[y])
                        {
                            c2[y] = 1 ;
                            ajoute = 1 ; // nouvelle composante connexe ajoutée
                        }
                    }
                }
            }
            // Composante fortement connexe c = intersection de c1 et c2
            for (x=0 ; x<ordre ; x++)
                c[x] = c1[x] & c2[x] ;
            // Retourner la composante fortement connexe c
            return c ;
        }
    }
}


// Fonction qui retourne un tableau dynamique de toutes les composantes fortement
// connexes du graphe
// Paramètres :
// adjacence : matrice d’adjacence nœud-nœud du graphe
// ordre : nombre de sommets
std::vector<std::vector<int>> Graph::toutesLesComposantesFortementConnexes (std::vector<std::vector<int>> adjacence, int ordre)
{
    // Variables locales
    std::vector<std::vector<int>> tabc ; // tableau dynamique des composantes fortement connexes à retourner
    std::vector<int> marques ; // tableau dynamique indiquant si les sommets sont marqués ou non
    int x, y ; // numéros de sommets intermédiaires comme indices des tableaux

    // Allouer les tableaux dynamiques tabc et marques de taille « ordre »
    tabc.resize(ordre);
    marques.resize(ordre);

    // Initialiser les valeurs de ces tableaux à 0
    for (int i = 0 ; i < ordre ; i++)
    {
        tabc[i].resize(ordre,0);
        marques[i] = 0;
    }
    // Pour tous les sommets x non marqués
    // Rechercher la composante fortement connexe de x
    // Marquer chaque sommet x et marquer les sommets y connectés à x et non marqués
    for (x=0 ; x<ordre ; x++)
    {
        if (!marques[x])
        {
            tabc[x] = uneComposanteFortementConnexe(adjacence, ordre, x) ;
            marques[x] = 1 ;
            for (y=0 ; y<ordre ; y++)
                if (tabc[x][y] && !marques[y])
                    marques[y] = 1 ;
        }
    }
    return tabc ;
}

std::vector<std::vector<int>> Graph::getAdjMatrix()
{
    std::vector<std::vector<int>> matrix;
    matrix.resize(vecSommet.size());

    for (int i = 0 ; i<vecSommet.size(); i++)
    {
        matrix[i].resize(vecSommet.size(),0);
    }
    for(int k=0; k<EdgeTab.size(); k++)
    {
        matrix[EdgeTab[k].geta().getidx()][EdgeTab[k].getb().getidx()]=1;
        matrix[EdgeTab[k].getb().getidx()][EdgeTab[k].geta().getidx()]=1;
    }

    for (int i = 0 ; i < matrix.size(); i++)
    {
        for (int j = 0 ; j <matrix[i].size(); j++)
        {
            std::cout << matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    return matrix;
}
