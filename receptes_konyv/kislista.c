//
// Created by Dominik on 2020. 11. 28..
//

#include "kislista.h"
#include "fuggvenyek.h"
#include <stdio.h>
#include <string.h>
#include "debugmalloc.h"

/*A hozzávalók kisebb láncolt listáját kezelõ függvények, hozzavalok.txt kezelése*/

void felszabadit_kisLista(KlistaElem *lista) {

    KlistaElem *egy = lista;
    while (egy != NULL) {
        KlistaElem *kov = egy->kov; /* következõ elem */
        if (egy->mennyiseg != NULL)
            free(egy->mennyiseg);
        if (egy->hozzavalo != NULL)
            free(egy->hozzavalo);
        free(egy);
        egy = kov;
    }
}
void hozzavalok_mentes(KlistaElem *lista) {
    FILE *hozz;
    hozz = fopen("hozzavalok.txt" , "w");

    KlistaElem *mozgo = lista;
    while (mozgo != NULL) {
        fprintf(hozz ,"%s\n", mozgo->hozzavalo);
        mozgo = mozgo->kov;
    }
    fprintf(hozz, "##");
    fclose(hozz);
}

KlistaElem *beolvasKisLista() {
    FILE *hozz;
    hozz = fopen("hozzavalok.txt", "r");

    long int ures = ftell(hozz); /*ha még nem létezne a fájl, akkor létrehozza és beleírja a végjelet*/
    printf("%ld", ures);
    if (ures == -1) {
        fclose(hozz);
        hozz = fopen("hozzavalok.txt", "w");
        fprintf(hozz, "##");
        fclose(hozz);
    }
    hozz = fopen("hozzavalok.txt" , "r");

    KlistaElem *beolv_hozz = NULL;

    char *ujSzo = NULL;
    int i = 0;
    while (strcmp((ujSzo = hosszu_sort_olvas_FILE(hozz)), "##") != 0) {
        KlistaElem *beolvSeged = (KlistaElem *) malloc(sizeof(KlistaElem));
        beolvSeged->mennyiseg = NULL;
        beolvSeged->hozzavalo = NULL;
        beolvSeged->kov = NULL;

        beolvSeged->hozzavalo = ujSzo;
        beolvSeged->sorszam = ++i;
        beolv_hozz = uj_elem_hozzafuz(beolv_hozz, beolvSeged);
    }
    free(ujSzo);
    fclose(hozz);
    return beolv_hozz;
}
KlistaElem *megvizsgal(KlistaElem *lista, KlistaElem *szo) {
    KlistaElem *mozgo = lista;
    while (mozgo != NULL) {
        if (strcmp(mozgo->hozzavalo, szo->hozzavalo) == 0)
            return lista;
        mozgo = mozgo->kov;
    }
    KlistaElem *ujElem = (KlistaElem*) malloc(sizeof(KlistaElem));
    ujElem->hozzavalo = (char*) malloc((strlen(szo->hozzavalo)+1)*sizeof(char));
    ujElem->mennyiseg = NULL;
    ujElem->kov = NULL;

    strcpy(ujElem->hozzavalo, szo->hozzavalo);


    lista = uj_elem_hozzafuz(lista, ujElem);
    hozzavalok_mentes(lista);

    return lista;
}
KlistaElem *egy_elem() {
    KlistaElem *seged = (KlistaElem*) malloc(sizeof(KlistaElem)); check(seged);
    seged->hozzavalo = NULL;
    seged->mennyiseg = NULL;
    seged->kov = NULL;

    printf("\nHozzávaló ('0', ha nincs több):\n");
    seged->hozzavalo = hosszu_sort_olvas();
    if (strcmp(seged->hozzavalo, "0") == 0)
        return seged;
    printf("Mennyiség? (Enter, ha nem fontos)\n");
    seged->mennyiseg = hosszu_sort_olvas();
    if (strcmp(seged->mennyiseg, "0") == 0) {
        free(seged->mennyiseg);
        seged->mennyiseg = "\n";
    }
    return seged;
}
KlistaElem *uj_elem_hozzafuz(KlistaElem *hozz_menny, KlistaElem *uj) {
    if (hozz_menny == NULL) {
        hozz_menny = uj;
        uj->kov = NULL;
    } else {
        int sorszam = 2;
        KlistaElem *mozgo = hozz_menny;
        while (mozgo->kov != NULL) {
            sorszam++;
            mozgo = mozgo->kov;
        }
        uj->sorszam = sorszam;
        uj->kov = NULL;
        mozgo->kov = uj;
    }
    return hozz_menny;
}
KlistaElem *fajlbol(KlistaElem *beolv_hozz) {
    int kivalszt = -1;
    printf("Válaszd ki a kívánt hozzávalót):\n"
           "--------------------------------\n");
    scanf("%d", &kivalszt);
    getchar();
    if (kivalszt == 0)
        return NULL;

    KlistaElem *uj = (KlistaElem*) malloc(sizeof(KlistaElem));  check(uj);
    uj->kov = NULL;
    KlistaElem *mozgo = beolv_hozz;
    while (mozgo->sorszam != kivalszt) {
        mozgo = mozgo->kov;
    }
    uj->hozzavalo = (char*) malloc((strlen(mozgo->hozzavalo)+1)*sizeof(char));
    strcpy(uj->hozzavalo, mozgo->hozzavalo);

    printf("Mennyiség?\n");
    uj->mennyiseg = hosszu_sort_olvas();
    if (strcmp(uj->mennyiseg, "0") == 0) {
        free(uj->mennyiseg);
        uj->mennyiseg = "\n";
    }
    return uj;
}