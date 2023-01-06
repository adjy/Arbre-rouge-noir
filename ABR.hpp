
#ifndef ABR_hpp
#define ABR_hpp

#include "entete.hpp"

/*ABR*/
Noeud *cle_min(Noeud *noeud, Noeud *ptr);
Noeud *cle_max(Noeud *noeud, Noeud *ptr);
Noeud *predecesseur(Noeud *noeud);
Noeud *successeur(Noeud *noeud);
Noeud *noeudValue(Noeud *noeud, int cle, Noeud *ptr);

void insertionABR(Noeud **racine, Noeud *noeudInserer); 



/* -------------ABR----------------*/
inline Noeud *cle_min(Noeud *noeud, Noeud *ptr){// Recherche la valeur minimale dans mon arbre
    if(noeud != NIL ){ 
        if(noeud->gauche == NIL) return noeud;
        ptr = cle_min(noeud->gauche, ptr);// Parcours sur mon sous-arbre gauche
    }
    return ptr;      
}

inline Noeud *cle_max(Noeud *noeud, Noeud *ptr){// Recherche la valeur maximale dans mon arbre
   if(noeud != NIL){
        if(noeud->droite == NIL) return noeud;
        ptr = cle_max(noeud->droite, ptr); // Parcours sur mon sous-arbre droite
    }
    return ptr;      
}

inline Noeud *predecesseur(Noeud *noeud){ // Recherche le predecesseur du noeud
    if(noeud != NIL){
        // recherche le max de son sous arbre gauche
        if(noeud->gauche != NIL) return cle_max(noeud->gauche, NIL);

        /*soit s’il n’a pas de sous-arbre gauche, le premier ancêtre dont le
            sous-arbre droit contient le noeud */
        Noeud *pere = noeud->pere;
        while(pere != NIL){
            if(pere->droite == noeud) return pere;
            noeud = pere;
            pere = pere->pere;
        }
        return pere;
    }
    return NIL;
}

inline Noeud *successeur(Noeud *noeud){ // Recherche le successeur du noeud
    if(noeud != NIL){
        //recherche le min de son sous arbre droite
        if(noeud->droite != NIL) return cle_min(noeud->droite, NIL);

        /*soit s’il n’a pas de sous-arbre droit, le premier ancêtre dont le
            sous-arbre gauche contient le noeud*/
        Noeud *pere = noeud->pere;
        while(pere != NIL){
            if(pere->gauche == noeud) return pere;
            noeud = pere;
            pere = pere->pere;
        }
        return pere;
    }
    return NIL;
}

inline void insertionABR(Noeud **racine, Noeud *noeudInserer){ //Insertion d'une valeur
    if(noeudInserer == nullptr) return;

    if(*racine == NIL || *racine == nullptr || (*racine)->cle == -999){
        *racine = noeudInserer;
        return;
    }
    

    Noeud *ptr = *racine;
    Noeud *pere = NIL;

    while(ptr != NIL){ // Parcours l'arbre 
        pere = ptr;
        // Si la valeur est inferieure que le noeud, donc je parcous dur le sous arbre gauche
        if(noeudInserer->cle < ptr->cle) ptr = ptr->gauche; 
        else ptr = ptr->droite; // Si la valeur est superieure que le noeud, donc je parcous dur le sous arbre droite
    }
     
    noeudInserer->pere = pere;

    //Ajout de mon noeud
    if(noeudInserer->cle < pere->cle) pere->gauche = noeudInserer;
    else pere->droite = noeudInserer; 
    // cout<<"Insertion completed successfully"<<endl;   
}


inline void supprimerABR(Noeud **noeud, Noeud *supp){ // Suppression d'un noeud
    if (*noeud == nullptr) {
        cout<<"L'arbre est vide! "<<endl;
        return;
    }

    if (supp == nullptr){
        cout<<"Le noeud n'existe pas!"<<endl;
        return;
    }

    //0 fils : le supprimer tout simplement ;
    if(supp->gauche == nullptr && supp->droite == nullptr){
        if (supp->pere == nullptr) {
            *noeud = nullptr;
            return;
        }
        if(supp == supp->pere->gauche) supp->pere->gauche = nullptr;
        else supp->pere->droite = nullptr;
        delete supp;
        return;     
    }

    //1 fils : on rattache ce fils au père du noeud à supprimer ;
    if(supp->gauche == nullptr || supp->droite == nullptr){
        Noeud *aRattacher;

        // Recherche si le fils gauche existe
        if(supp->gauche != nullptr) aRattacher = supp->gauche; // recupere le fils du noeud a supprimer
        
        // Recherche si le fils droit existe
        else aRattacher = supp->droite; // recupere le fils du noeud a supprimer
        
        aRattacher->pere = supp->pere;// raccorde le noeud au pere du noeud a supprimer

        // Si le noeud appartient au sous-arbre gauche
        
        if(supp->pere == nullptr){
            (*noeud) = aRattacher;
            return;
        } 
        if(supp == supp->pere->gauche) supp->pere->gauche = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        else supp->pere->droite = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        
        delete supp;
        return; 
    }

    /*2 fils :
        1 on recherche son successeur (= qui a au plus un fils),
        2 on copie la valeur du successeur dans le noeud a supprimer 
        3 on supprime le successeur.
    */

    Noeud *succ = successeur(supp); // recherche de son successeur
    if (succ == nullptr){
        cout<<"Le noeud n'a pas de successeur! "<<endl;
        return;
    } 
    supp->cle = succ->cle; //on copie la valeur du successeur dans le noeud a supprimer
    supprimerABR(noeud, succ); // on supprime le successeur
}
inline Noeud *noeudValue(Noeud *noeud, int cle, Noeud *ptr){// FOnction qui recherche l'existance d'une valeur
    if(noeud != NIL){
        if(noeud->cle == cle) return noeud; // Si il retrouve la valeur, il le renvoi
        else{ // Sinon, il parcours son fils gauche et droite
            ptr = noeudValue(noeud->gauche, cle,ptr);
            ptr = noeudValue(noeud->droite, cle,ptr);
        }     
    }
    return ptr; // Retour la valeur de ptr
}



#endif




