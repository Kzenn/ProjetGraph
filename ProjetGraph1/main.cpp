#include <iostream>
#include "Graph.hpp"

using namespace std;

int main()
{
    Graph g;
    std::string choix;

    std::cout << "Entrer le nom du fichier : " << std::endl;
    std::cin >> choix;
    g.FileReading(choix);
    return 0;
}
