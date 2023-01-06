

/*Mes fonctions */
#include "ABR.hpp"
#include "RN.hpp"



int main(){
    NIL->color = 'N';
    
    Noeud *noeud = initArbre();
    // createUser(&noeud, nullptr);
    
    // afficheP(noeud);cout<<endl;
  
    cout<<endl;
    /*888888888888888888888888888888888888888888888*/
    /*Noeud *NI = createNode(11);
    NI->color = 'N';
    insertionABR(&noeud, NI);

    NI = createNode(2);
    NI->color = 'R';
    insertionABR(&noeud, NI);

    NI = createNode(1);
    NI->color = 'N';
    insertionABR(&noeud, NI);

    NI = createNode(7);
    NI->color = 'N';
    insertionABR(&noeud, NI);

    NI = createNode(5);
    NI->color = 'R';
    insertionABR(&noeud, NI);

    NI = createNode(8);
    NI->color = 'R';
    insertionABR(&noeud, NI);

    NI = createNode(14);
    NI->color = 'N';
    insertionABR(&noeud, NI);

    NI = createNode(15);
    NI->color = 'R';
    insertionABR(&noeud, NI);
    afficheP(noeud);cout<<endl;
    */
/**************************************************************************************/
   

    // Insertion(&noeud, createNode(4));
    // Insertion(&noeud, createNode(13));

    Insertion(&noeud, createNode(41));
    Insertion(&noeud, createNode(38));
    Insertion(&noeud, createNode(31));
    Insertion(&noeud, createNode(12));
    Insertion(&noeud, createNode(19));
    Insertion(&noeud, createNode(8));
    afficheP(noeud);cout<<endl;



    MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 8, NIL));
     MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 12, NIL));
     MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 19, NIL));

     MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 31, NIL));
     MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 38, NIL));
     MAJ_ARN_supprimer(&noeud,noeudValue(noeud, 41, NIL));


    afficheP(noeud);cout<<endl;


    cout<<"Fin";
    delete NIL;
    return 0;

}

