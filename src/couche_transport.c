#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"
#include "application.h"

/* ************************************************************************** */
/* *************** Fonctions utilitaires couche transport ******************* */
/* ************************************************************************** */

// RAJOUTER VOS FONCTIONS DANS CE FICHIER...

uint8_t generer_control(paquet_t paquet){
    uint8_t somme = 0;
    /* XOR sur le type, num_seq, lg_info */
    somme ^= paquet.type;
    somme ^= paquet.num_seq;
    somme ^= paquet.lg_info;

    /* XOR sur les données du paquet */
    for (int i = 0; i < paquet.lg_info; i++) {
        somme ^= paquet.info[i];
    }

    return somme;
}

bool verifier_controle(paquet_t paquet){
    return paquet.somme_ctrl == generer_control(paquet);
}

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);
}
