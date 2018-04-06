#include "Graph.hpp"
#define SCREEN_H 768
#define SCREEN_W 1024

#define TAILLEX 100
#define TAILLEY 100

void thick_line(BITMAP *bmp, int x, int y, int x_, int y_,int thickness, int color)
{
    int dx = x - x_;
    int dy = y - y_;
    int d = sqrtf(dx * dx + dy * dy);
    if (!d)
        return;
    int v[8];
    v[0] = x - thickness * dy / d;
    v[1] = y + thickness * dx / d;
    v[2] = x + thickness * dy / d;
    v[3] = y - thickness * dx / d;
    v[4] = x_ + thickness * dy / d;
    v[5] = y_ - thickness * dx / d;
    v[6] = x_ - thickness * dy / d;
    v[7] = y_ + thickness * dx / d;
    polygon(bmp, 4.9, v, color);
}

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
unsigned int Graph::getOrder()
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

std::vector<std::vector<int>> Graph::getAdjMatrix()
{
    return AdjMatrixSucc;
}

std::vector<int> Graph::getTabComposante()
{
    return m_tab_composantes;
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

void Graph::BuildAdjMatrix()
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
    AdjMatrixSucc = matrix ;
}

void Graph::Malgrange()
{
    std::vector<int>m_alpha;
    std::vector<int>m_beta;
    m_size_alpha = vecSommet.size();

    /*La méthode de Malgrange (améliorée) consiste à calculer Ã=(I+B)^k avec k>=nb_sommets-1 et k=2^i
    																	     B la matrice associée au graphe
    																	     I l'identité
      A partir de cette matrice on regarde quels sont les éléments qui vérifient Ã(i,j)=Ã(j,i)=1.
      Ces éléments appartiennent alors à la même composante fortement connexe du graphe (facilement démontrable)*/

    std::vector<std::vector<int>> I;//Matrice identité
    std::vector<std::vector<int>> mat;


    int i,j,k;

    I.resize(vecSommet.size());
    mat.resize(vecSommet.size());
    m_beta.resize(vecSommet.size()*vecSommet.size());
    m_alpha.resize(vecSommet.size());


    for (int i = 0 ; i<vecSommet.size(); i++)
    {
        I[i].resize(vecSommet.size(),0);
        mat[i].resize(vecSommet.size(),0);
    }


    for (i=0; i<m_size_alpha; i++)
    {
        for(j=0; j<m_size_alpha; j++)
        {
            if(j==i)
                I[i][j]=1;
            else
                I[i][j]=0;

            if( (AdjMatrixSucc[i][j]+I[i][j]) >= 1 )
                mat[i][j]=1;		//La matrice reste booléènne (I+B)
            else
                mat[i][j]=0;
        }
    }


    /*Calcul de (I+B)^k  avec k=2^i*/

    for(k=1; k<2*m_size_alpha; k*=2)
    {
        mat=Produit_matriciel(mat,mat,m_size_alpha);
    }

    AdjMatrixSucc=mat;	///la matrice associée au graphe de vient (I+B)^k  avec k>=n-1  où n est le nombre de sommets

    /* Methode de Malgrange : Ã(i,j)=Ã(j,i)=1 ?? */

    m_tab_composantes.resize(vecSommet.size());

    for(i=0; i<m_size_alpha; i++)
    {
        m_tab_composantes.resize(vecSommet.size(),0);
    }

    for(i=0; i<m_size_alpha; i++)
    {
        if (m_tab_composantes[i]==0)
            m_tab_composantes[i]=1;

        for (j=0; j<m_size_alpha; j++)
        {
            if(AdjMatrixSucc[i][j]==1  &&  AdjMatrixSucc[j][i]==1)  //c'est ici que l'on verifie Ã(i,j)=Ã(j,i)=1
                m_tab_composantes[j]=i;	//on ajoute l'élément (i,j) de graph_mat à la composante fortement connexe
        }

    }
    std::cout<<std::endl<<std::endl;

}

std::vector<std::vector<int>> Graph::Produit_matriciel(std::vector<std::vector<int>> A,std::vector<std::vector<int>>B,int s)
{
    int i,j,k;

    /*Initialisation de la matrice résultante*/
    std::vector<std::vector<int>> res;
    res.resize(vecSommet.size());

    for (int i = 0 ; i<vecSommet.size(); i++)
    {
        res[i].resize(vecSommet.size(),0);
    }

    for(i=0; i<s; i++)
    {
        for(j=0; j<s; j++)
            res[i][j]=0;
    }
    /*Fin initialisation*/


    /*Forme la matrice produit de A par B et la stocke dans res*/
    for(i=0; i<s; i++)
    {
        for(j=0; j<s; j++)
        {
            for(k=0; k<s; k++)
            {
                res[i][j]+=A[i][k]*B[k][j];
            }
            if(res[i][j]>=1)
                res[i][j]=1;//La matrice reste booléènne
            else
                res[i][j]=0;
        }

    }
    /*Fin calcul du produit*/

    return res;
}

void Graph::Affiche_composantes_FC(BITMAP* buffer)
{
    srand(time(NULL));
    std::cout<<"---------CFC---------"<<std::endl<<std::endl;

    int i=0,j=0,k=0,numero=1;
    int c1, c2, c3;


    std::vector<int> composante;	//un tableau représentant une composante (on utilise le même pour les autres composantes
    composante.resize(vecSommet.size()+3);

    for (i=0; i<vecSommet.size()+3; i++)
        composante[i]=(-1);		//initialisation à -1

    i=0;


    while (i<vecSommet.size())		///toutes les valeurs possibles que tab_composantes contient
    {
        for(j=0; j<m_tab_composantes.size(); j++)	///parcours de tab_composantes
        {
            if (m_tab_composantes[j]==i)	///si la composante i existe
            {
                composante[k]=j;	///on met le/les sommet(s) qui appartien(t)(nent) à cette composante
                k++;

            }
        }


        k=0;

        if(composante[0]!=(-1))	///si la composante i existe
        {
            c1 = rand()%255;
            c2 = rand()%255;
            c3 = rand()%200;
            std::cout<<"Composante "<<numero<<" : ";

            j=0;

            while(composante[j]!=(-1))//on l'affiche
            {
                std::cout<<"["<<composante[j]<<"] ";
                vecSommet[composante[j]]->setcolor(makecol(c1,c2,c3));
                rectfill(buffer,vecSommet[composante[j]]->getpos_x()-10,vecSommet[composante[j]]->getpos_y()-10,vecSommet[composante[j]]->getpos_x()+TAILLEX+10,vecSommet[composante[j]]->getpos_y()+TAILLEY+10,makecol(c1,c2,c3));

                ///MEME COULEUR DANS EDGE TAB ET SOMMET TAB
                for(int j = 0 ; j<EdgeTab.size(); j++)
                {
                    for(int p = 0 ; p<vecSommet.size(); p++)
                    {
                        if(EdgeTab[j].geta().getchemin()==vecSommet[p]->getchemin())
                        {
                            EdgeTab[j].geta().setcolor(vecSommet[p]->getcolor());
                        }
                        if(EdgeTab[j].getb().getchemin()==vecSommet[p]->getchemin())
                        {
                            EdgeTab[j].getb().setcolor(vecSommet[p]->getcolor());
                        }
                    }
                }

                for(auto& elem : EdgeTab)
                {
                    if(elem.geta().getcolor() == elem.getb().getcolor() && elem.geta().getcolor()!=-1 && elem.getb().getcolor()!=-1)
                    {
                        if(elem.getWeight()<51)
                            line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, elem.geta().getcolor());
                        else if (elem.getWeight()>50 && elem.getWeight()<251)
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 5.0, elem.geta().getcolor());
                        else if (elem.getWeight()>200 && elem.getWeight()<501)
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 10.0, elem.geta().getcolor());
                        else
                            thick_line(buffer, elem.geta().getpos_x()+TAILLEX/2, elem.geta().getpos_y()+TAILLEY/2, elem.getb().getpos_x()+TAILLEX/2, elem.getb().getpos_y()+TAILLEY/2, 16.0, elem.geta().getcolor());
                    }
                }

                j++;
            }

            std::cout<<std::endl;

            j=0;

            while(j<vecSommet.size())
            {
                composante[j]=(-1);	///on la reinitialise
                j++;
            }
            numero++;	///on incrémente l'indice de la composante
        }

        i++;	///on passe au numero (calculé) de la composante suivante
    }

    composante.clear();	//composante devient obsolète : on le libère

}

void Graph::Affiche_Mat()
{
    std::cout<<std::endl<<std::endl;

    for (int i=0; i<vecSommet.size(); i++)
    {
        for (int j=0; j<vecSommet.size(); j++)
        {
            std::cout<<(int)AdjMatrixSucc[i][j]<<"  ";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl<<std::endl;
}
