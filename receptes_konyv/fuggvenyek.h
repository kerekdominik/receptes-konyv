//
// Created by Dominik on 2020. 11. 12..
//

#ifndef RECEPTES_TISZTAZAT_FUGGVENYEK_TIPUSOK_H
#define RECEPTES_TISZTAZAT_FUGGVENYEK_TIPUSOK_H

#include "nagylista.h"
#include <stdbool.h>

/*fuggvenyek*/

void check(void *p);

char *hosszu_sort_olvas();
char *hosszu_sort_olvas_FILE(FILE *file);

void hozzavalo_keres(ListaElem *aktualis, char *keresett, char* seged);
bool hozzavalo_keresTobb(ListaElem *aktualis, KlistaElem *keresett);

void reszletek(NagyLista *rec_konyv);
KlistaElem *el_kellHozzavalok();
void torles(NagyLista *rec_konyv);

void eddigiek_kiir(int almenu, KlistaElem *kisList_uj, ListaElem *uj_beolvasott);
KlistaElem *almenuFGV(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje, int almenu);
KlistaElem *uj(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje);
KlistaElem  *fajl(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje);


#endif //RECEPTES_TISZTAZAT_FUGGVENYEK_TIPUSOK_H
