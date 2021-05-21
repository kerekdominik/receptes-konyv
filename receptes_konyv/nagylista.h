//
// Created by Dominik on 2020. 11. 28..
//

#ifndef RECEPTES_TISZTAZAT_NAGYLISTA_H
#define RECEPTES_TISZTAZAT_NAGYLISTA_H

#include <stdio.h>
#include "kislista.h"

typedef struct listElem {
    int sorszam;
    char *nev;
    KlistaElem *hozz_menny;
    char *elkeszites;

    struct listElem *elozo, *kov;
}ListaElem;
typedef struct nagyLista {
    ListaElem *elso;
    ListaElem *utolso;
}NagyLista;

NagyLista *mentes_beolvas();

void felszabadit_egesz(NagyLista *felszabaditando);
void mentes(NagyLista *rec_konyv);
void hozzafuz(NagyLista *rec_konyv, ListaElem *uj);


#endif //RECEPTES_TISZTAZAT_NAGYLISTA_H
