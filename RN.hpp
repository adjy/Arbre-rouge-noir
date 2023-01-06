
#ifndef RN_hpp
#define RN_hpp
#include "entete.hpp"
#include "ABR.hpp"

/*RN*/
Noeud *initArbre();
Noeud *createNode(int cle);
Noeud *uncle(Noeud *noeud);

void createUser(Noeud **noeud, Noeud *pere);

void affiche(Noeud *racine);
void afficheP(Noeud *racine);

void rotationDroite(Noeud **racine, Noeud *x);
void rotationGauche(Noeud **racine, Noeud *y);

void Insertion(Noeud **racine, Noeud *noeud_inserer);
void CorrigeColor(Noeud **racine, Noeud *noeud_inserer);
void Insertion_Cas1(Noeud **racine, Noeud *noeud_inserer);
void Insertion_Cas2(Noeud **racine, Noeud *noeud_inserer);
void Insertion_Cas3(Noeud **racine, Noeud *noeud_inserer);

Noeud *suppressionRN(Noeud **noeud, Noeud *supp);
void corrigeCouleurSupp(Noeud **noeud, Noeud *supp);
void MAJ_ARN_supprimer(Noeud **noeud, Noeud *supp);
void suppCas1(Noeud **racine, Noeud *supp);
void suppCas2(Noeud **racine, Noeud *supp);
void suppCas3(Noeud **racine, Noeud *supp);
void suppCas4(Noeud **racine, Noeud *supp);

/* Mes fonctions RN*/
inline Noeud *initArbre(){ //Initialisation de mon arbre
    Noeud *Arbre = new Noeud();
    Arbre->cle = -999;
    Arbre->pere = NIL;
    Arbre->gauche = NIL;
    Arbre->droite = NIL;  
    return Arbre;
}

inline Noeud *createNode(int cle){
    Noeud *noeud = new Noeud;
    noeud->cle = cle;
    noeud->pere = NIL;   
    noeud->gauche = NIL;
    noeud->droite = NIL;
    return noeud;
}

inline void createUser(Noeud **noeud, Noeud *pere){
    if(*noeud != NIL){ 
        (*noeud)->pere = pere; // raccorde le pere du noeud
       
       //Demande l'existance des fils gauches et droites
        string fg, fd;   
        cout<<"Val? ";
        cin>>(*noeud)->cle;

        cout<<"Couleur? (R/N) ";
        cin>>(*noeud)->color;

        cout<<"fg? (oui/non) ";
        cin>>fg;
        cout<<"fd? (oui/non)";
        cin>>fd;

        //Affecte aux fils le noeud NIL
        (*noeud)->gauche = NIL;
        (*noeud)->droite = NIL;


        if(fg == "oui"){ // Si oui pour le fils gauche, appel la fonction sur le fils gauche
            (*noeud)->gauche = new Noeud;
            createUser(&(*noeud)->gauche, *noeud);
        }

        if(fd == "oui"){ // Si oui pour le fils droite, appel la fonction sur le fils droite
            (*noeud)->droite = new Noeud;
            createUser(&(*noeud)->droite, *noeud);
        }        
    }
}

inline void affiche(Noeud *racine){ // Affichage des valeurs d'un arbre binaire de maniere infixe

    Noeud *ptr = racine;
    if (ptr != NIL){
        affiche(ptr->gauche);
        cout<< ptr->cle<<" couleur: "<<ptr->color<<endl;     
        affiche(ptr->droite);
    }  
}
inline void afficheP(Noeud *racine){ // Affichage des valeurs d'un arbre binaire de maniere infixe

    Noeud *ptr = racine;
    if (ptr != NIL){       
        cout<< ptr->cle<<" couleur: "<<ptr->color<<endl;     
        afficheP(ptr->gauche);   
        afficheP(ptr->droite);
    }  
}

inline void rotationDroite(Noeud **racine, Noeud *y) {
    Noeud *x = y->gauche;
    Noeud *beta = x->droite;

    Noeud *pere = y->pere;
    if(pere == NIL) 
        *racine = x;
    else if(pere->gauche == y) 
        pere->gauche = x;
    else 
        pere->droite = x;

    x->pere = pere;
    x->droite = y;
    y->pere = x;
    y->gauche = beta;

    if (beta != NIL)
        beta->pere = y;
}
inline void rotationGauche(Noeud **racine, Noeud *x) {
    Noeud *y = x->droite;
    Noeud *alpha = x->gauche;
    Noeud *beta = y->gauche;
    Noeud *gama = y->droite;

    Noeud *pere = x->pere;
    if(pere == NIL) 
        *racine = y;
    else if(pere->gauche == x) 
        pere->gauche = y;
    else 
        pere->droite = y;

    y->pere = pere;
    y->gauche = x;
    x->pere = y;
    x->droite = beta;
    if (beta != NIL)
        beta->pere = x;
}

inline void Insertion(Noeud **racine, Noeud *inserer){
     // Permet de faire l'insertion d'un noeud
    if(inserer == nullptr || inserer == NIL) 
        return; // Ne fait rien si le noeud a inserer est null

    inserer->color = 'R'; //Affecte au noeud la couleur rouge
    insertionABR(racine, inserer); // Fait l'insertion de maniere d'un abr quelq
    CorrigeColor(racine, inserer); // Permet de corriger les couleurs  
}

inline Noeud *uncle(Noeud *noeud){
    if(noeud == NIL || noeud->pere == NIL || noeud->pere->pere == NIL) 
        return NIL;
    
    Noeud *gp = noeud->pere->pere;
    Noeud *pere = noeud->pere ;
    Noeud *uncle = NIL;

    if(gp->gauche == pere) uncle = gp->droite;
        
    else if (gp->droite == pere) uncle = gp->gauche;
    return uncle;   
}

inline void CorrigeColor(Noeud **racine, Noeud *inserer){
  
    if(inserer == *racine) 
        inserer->color ='N';
    else if(inserer->pere->color == 'N') 
        return;

    else if( uncle(inserer) != NIL && uncle(inserer)->color == 'R') 
        Insertion_Cas1(racine,inserer);
    else 
        Insertion_Cas2(racine, inserer);
    
    (*racine)->color = 'N';
}

inline void Insertion_Cas1(Noeud **racine, Noeud *inserer){
    // Cas 1
    /*  
        - on colorie le père et l’oncle de x en noir et le grand-père en rouge ;
        - ce cas 1 peut engendrer une nouvelle itération si le père du grand-père
            qu’on vient de mettre à rouge est rouge, le grand-père devient x et
            donc si son oncle est lui-même rouge, on recommence ce cas 1.
    */
    // cout<<"cas1"<<endl;

    if(inserer != *racine && inserer->pere->color == 'R'){
        Noeud *pere = inserer->pere ;
        Noeud *gp = inserer->pere->pere;
        Noeud *oncle = uncle(inserer);

        if(oncle != NIL && oncle->color == 'R'){
            pere->color = 'N';
            oncle->color = 'N';
            gp->color = 'R';
            CorrigeColor(racine,gp);
        }    
    }
    else    
        Insertion_Cas2(racine, inserer);

}


inline void Insertion_Cas2(Noeud **racine, Noeud *inserer){
    /*
        Cas 2 : y oncle est noir, x est un fils droit
        - on fait une rotation à gauche sur le père de x (A),
        - le père de x (A) devient un fils gauche et x (B) devient son père,
        - on arrive au cas 3 où le père de x (A) devient le nouveau x à
            considérer (noeud rouge x avec père rouge et oncle y noir).
    */
    // cout<<"cas2"<<endl;

    Noeud *pere = NIL;
    Noeud *gp = NIL;

    pere = inserer->pere ;
    if(pere != NIL) gp = inserer->pere->pere;

    if(gp != NIL && gp->gauche->droite == inserer) {
        rotationGauche(racine, pere);
        inserer = inserer->gauche;
    }
    else if(gp != NIL  && gp->droite->gauche == inserer){
        rotationDroite(racine, pere);
        inserer = inserer->droite;
    } 

    Insertion_Cas3(racine, inserer);
}


inline void Insertion_Cas3(Noeud **racine, Noeud *inserer){
    /*
        Cas 3 : oncle y est noir, x est un fils gauche
        - on va faire une rotation à droite sur le grand-pere de x noté gpx,
            gpx devient rouge,
        - le père de x noté px devient le père de gpx et devient noir
    */
    // cout<<"cas3"<<endl;
    Noeud *pere = NIL;
    Noeud *gp = NIL;

    pere = inserer->pere ;
    if(pere != NIL) gp = inserer->pere->pere;

    if(gp != NIL && pere->gauche == inserer) rotationDroite(racine, gp);   
    else if(gp != NIL && pere->droite == inserer) rotationGauche(racine, inserer);

    gp->color = 'R';
    pere->color = 'N';
    
}

inline void AjoutNIL(Noeud **noeud){
    if(*noeud != NIL && *noeud != nullptr){
        if( (*noeud)->droite == nullptr && (*noeud)->gauche == nullptr){
            (*noeud)->droite = NIL;
            (*noeud)->gauche = NIL;
        }
        AjoutNIL(&(*noeud)->gauche);
        AjoutNIL(&(*noeud)->droite);     
    }   
}


inline Noeud *suppressionRN(Noeud **noeud, Noeud *supp){ // Suppression d'un noeud
    if (*noeud == NIL) {
        cout<<"L'arbre est vide! "<<endl;
        return NIL;
    }

    if (supp == NIL){
        cout<<"Le noeud n'existe pas!"<<endl;
        return NIL;
    }

    //0 fils : le supprimer tout simplement ;
    if(supp->gauche == NIL && supp->droite == NIL){
        if (supp->pere == NIL) {
            *noeud = NIL;
            return NIL;
        }
        if(supp == supp->pere->gauche) supp->pere->gauche = NIL;
        else supp->pere->droite = NIL;

        // delete supp;
        return supp;     
    }

    //1 fils : on rattache ce fils au père du noeud à supprimer ;
    if( supp->gauche == NIL || supp->droite == NIL){
        Noeud *aRattacher;

        // Recherche si le fils gauche existe
        if(supp->gauche != NIL) aRattacher = supp->gauche; // recupere le fils du noeud a supprimer
        
        // Recherche si le fils droit existe
        else aRattacher = supp->droite; // recupere le fils du noeud a supprimer
        
        aRattacher->pere = supp->pere;// raccorde le noeud au pere du noeud a supprimer

        // Si le noeud appartient au sous-arbre gauche
        
        if(supp->pere == NIL){
            (*noeud) = aRattacher;
            return supp;
        } 
        if(supp == supp->pere->gauche) supp->pere->gauche = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        else supp->pere->droite = aRattacher; // Raccorde le pere du noeud a supprimer a aRattacher
        
        // delete supp;
        return supp; 
    }

    /*2 fils :
        1 on recherche son successeur (= qui a au plus un fils),
        2 on copie la valeur du successeur dans le noeud a supprimer 
        3 on supprime le successeur.
    */

    Noeud *succ = successeur(supp); // recherche de son successeur
    if (succ == NIL){
        cout<<"Le noeud n'a pas de successeur! "<<endl;
        return NIL;
    } 
    supp->cle = succ->cle; //on copie la valeur du successeur dans le noeud a supprimer
    suppressionRN(noeud, succ); // on supprime le successeur
    return NIL;
    
}

inline Noeud *brother(Noeud *noeud){
    if(noeud->pere != NIL){
        Noeud *pere = noeud->pere;
        if(pere->droite == noeud) 
            return pere->gauche;
        else 
            return pere->droite;
    }
    return NIL;
}

inline void suppCas1(Noeud **racine, Noeud *supp){
    // cout<<"cas 1"<<endl;
    Noeud *bro = brother(supp);
    Noeud *pere = bro->pere;

    bro->color = 'N';
    pere->color = 'R';

    if(supp == pere->gauche)
        rotationGauche(racine, pere);
    else
        rotationDroite(racine, pere);
}

inline void suppCas2(Noeud **racine, Noeud *supp){
    // cout<<"cas 2"<<endl;

    Noeud *bro = brother(supp);
    Noeud *pere = bro->pere;

    bro->color = 'R';
    // pere->color = 'N';

    corrigeCouleurSupp(racine, pere);
    // cout<<"Fin cas 2"<<endl;
}

inline void suppCas3(Noeud **racine, Noeud *supp){
    // cout<<"cas 3"<<endl;

    Noeud *bro = brother(supp);
    Noeud *pere = bro->pere;
    char colTemp;

    if( bro->gauche->color == 'R' && bro->droite->color == 'N' && supp == pere->gauche) {
        colTemp = bro->color;
        bro->color = bro->gauche->color;
        bro->gauche->color = colTemp;
        supp = bro->gauche;
        rotationDroite(racine, bro);
    }

    else if( bro->droite->color == 'R' && bro->gauche->color == 'N' && supp == pere->droite) {
        colTemp = bro->color;
        bro->color = bro->droite->color;
        bro->droite->color = colTemp;
        supp = bro->droite;
        rotationGauche(racine, bro);
    }

    suppCas4(racine, supp);
}

inline void suppCas4(Noeud **racine, Noeud *supp){
    // cout<<"cas 4"<<endl;

    Noeud *bro = brother(supp);
    Noeud *pere = bro->pere;
    
    bro->color = pere->color;
    pere->color = 'N';

    if(supp == bro->gauche){
        
        bro->droite->color = 'N';
        rotationGauche(racine, pere);
    }
    else{
        bro->gauche->color = 'N';
        rotationDroite(racine, pere);
    }
}

inline void MAJ_ARN_supprimer(Noeud **noeud, Noeud *supp){
    Noeud *suppReel = suppressionRN(noeud, supp);
    if(suppReel != NIL && supp->color == 'N')
        corrigeCouleurSupp(noeud, suppReel);
    
    delete suppReel;

}

inline void corrigeCouleurSupp(Noeud **noeud, Noeud *supp){
    if(supp->color == 'R')
        supp->color = 'N';

    else{
        if(supp != *noeud && supp->color == 'N'){
            Noeud * bro = brother(supp);

            if(bro != NIL && bro->color == 'R')
                suppCas1(noeud, supp);

            else if(bro != NIL && bro->color == 'N'){

                if(bro->gauche->color == 'N' && bro->droite->color == 'N')
                    suppCas2(noeud, supp);
                else
                    suppCas3(noeud, supp);
                // if(bro->droite->color == 'R')
                //     suppCas4(noeud, supp);
            }

        }
    }
    (*noeud)->color = 'N';

}

#endif