#include "debugmalloc.h"
#include "nagylista.h"
#include "fuggvenyek.h"

NagyLista *mentes_beolvas() {
    /*NagyLista létrehozása*/
    NagyLista *rec_konyv = (NagyLista*) malloc(sizeof(NagyLista)); check(&rec_konyv);
    rec_konyv->elso = (ListaElem*) malloc(sizeof(ListaElem)); check(&rec_konyv->elso);
    rec_konyv->utolso = (ListaElem*) malloc(sizeof(ListaElem)); check(&rec_konyv->utolso);
    rec_konyv->elso->sorszam = 0;
    rec_konyv->utolso->kov = NULL;

    rec_konyv->elso->kov = rec_konyv->utolso;
    rec_konyv->utolso->elozo = rec_konyv->elso;

    FILE *receptek;
    receptek = fopen("receptek.txt" , "r");

    long int ures = ftell(receptek); /*ha még nem létezne a fájl, akkor létrehozza és beleírja a végjelet*/
    if (ures == -1) {
        fclose(receptek);
        receptek = fopen("receptek.txt", "w");
        fprintf(receptek, "###");
        fclose(receptek);
    }
    receptek = fopen("receptek.txt" , "r");

    char *seged;
    int i = 0;
    while (strcmp((seged = hosszu_sort_olvas_FILE(receptek)), "###") != 0){

        ListaElem *be = (ListaElem*) malloc(sizeof(ListaElem)); check(be);

        be->nev = seged;

        be->hozz_menny = NULL;
        while (strcmp((seged = hosszu_sort_olvas_FILE(receptek)), "#hozzv") != 0) {
            KlistaElem *uj = (KlistaElem*) malloc(sizeof(KlistaElem)); check(uj);
            uj->kov = NULL;

            uj->hozzavalo = seged;
            uj->mennyiseg = hosszu_sort_olvas_FILE(receptek);
            be->hozz_menny = uj_elem_hozzafuz(be->hozz_menny, uj);
        }
        free(seged);

        seged = hosszu_sort_olvas_FILE(receptek);
        be->elkeszites = seged;

        be->sorszam = ++i;
        hozzafuz(rec_konyv, be);

    }
    free(seged);

    fclose(receptek);
    return rec_konyv;
}

void felszabadit_egesz(NagyLista *rec_konyv) {
    ListaElem *egy = rec_konyv->elso;
    rec_konyv->elso->hozz_menny = NULL;
    rec_konyv->utolso->hozz_menny = NULL;
    rec_konyv->elso->nev = NULL;
    rec_konyv->elso->elkeszites = NULL;
    rec_konyv->utolso->nev = NULL;
    rec_konyv->utolso->elkeszites = NULL;

    while (egy != NULL) {
        ListaElem *kov = egy->kov; /* következõ elem */
        if (egy->hozz_menny != NULL)
            felszabadit_kisLista(egy->hozz_menny);
        if (egy->nev != NULL)
            free(egy->nev);
        if (egy->elkeszites != NULL)
            free(egy->elkeszites);
        free(egy);
        egy = kov;
    }
    free(rec_konyv);
}
void mentes(NagyLista *rec_konyv) {
    FILE *receptek;
    receptek = fopen("receptek.txt", "w");

    ListaElem *mozgo = rec_konyv->elso->kov;
    while (mozgo->kov != NULL) {
        fprintf(receptek, "%s\n", mozgo->nev);

        KlistaElem *kmozgo = mozgo->hozz_menny;
        while (kmozgo != NULL) {
            if ( kmozgo->mennyiseg != NULL) {
                fprintf(receptek, "%s\n", kmozgo->hozzavalo);
                fprintf(receptek, "%s\n", kmozgo->mennyiseg);
            } else {
                fprintf(receptek, "%s\n", kmozgo->hozzavalo);
            }
            kmozgo = kmozgo->kov;
        }
        fprintf(receptek, "#hozzv\n");
        fprintf(receptek, "%s\n", mozgo->elkeszites);

        mozgo = mozgo->kov;
    }
    fprintf(receptek, "###\n");

    fclose(receptek);
}
void hozzafuz(NagyLista *rec_konyv, ListaElem *uj) {
    uj->elozo = rec_konyv->utolso->elozo; //az utolso elottire mutat az uj
    uj->kov = rec_konyv->utolso; //az uj kovetkezoje az utolso elemre mutat, ami a strázsa
    rec_konyv->utolso->elozo->kov = uj; //az utolso elotti mutat az uj-ra
    rec_konyv->utolso->elozo = uj;
}