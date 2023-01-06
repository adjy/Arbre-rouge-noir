
#ifndef entete_hpp
#define entete_hpp

#include <iostream>
using namespace std;

struct Noeud{
    int cle;
    char color = 'N';
    Noeud *pere = nullptr;   
    Noeud *gauche = nullptr;
    Noeud *droite = nullptr;   
};
Noeud *NIL = new Noeud;


#endif