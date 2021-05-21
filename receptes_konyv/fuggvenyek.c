//
// Created by Dominik on 2020. 11. 12..
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"
#include "kislista.h"
#include "nagylista.h"
#include "fuggvenyek.h"

/*mem�riafoglal�s ellen�rz�se*/
void check(void *p) {
    if (p == NULL)
        printf("Nem sikerult...");
}

/*dinamikus beolvas�s*/
char *hosszu_sort_olvas() { //forras: https://infoc.eet.bme.hu/lab08/#4
    int db = 0;
    char *sor = (char *) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
        /* itt a t�mb ny�jt�sa */
        char *ujtomb = (char *) malloc(sizeof(char) * (db + 1 + 1));
        for (int i = 0; i < db; ++i)
            ujtomb[i] = sor[i];
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db + 1] = '\0';
        ++db;
    }
    return sor;
}
char *hosszu_sort_olvas_FILE(FILE *file) { //forras: https://infoc.eet.bme.hu/lab08/#4 - csak �talak�tva f�jl olvas�sra
    int db = 0;
    char *sor = (char *) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    while (fscanf(file ,"%c", &ujkar) == 1 && ujkar != '\n') {
        /* itt a t�mb ny�jt�sa */
        char *ujtomb = (char *) malloc(sizeof(char) * (db + 1 + 1));
        for (int i = 0; i < db; ++i)
            ujtomb[i] = sor[i];
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db + 1] = '\0';
        ++db;
    }
    return sor;
}

/*seg�df�ggv�nyek a men�pontokhoz*/
void hozzavalo_keres(ListaElem *aktualis, char *keresett, char *seged) {
    KlistaElem *mozgo = aktualis->hozz_menny;
    while (mozgo != NULL) {
        if (strcmp(mozgo->hozzavalo, keresett) == 0 || strcmp(mozgo->hozzavalo, seged) == 0)
            printf("\t%d. %s\n", aktualis->sorszam, aktualis->nev);
        mozgo = mozgo->kov;
    }
}
bool hozzavalo_keresTobb(ListaElem *aktualis, KlistaElem *keresett) {
    KlistaElem *mozgo;
    int db=0;
    mozgo = keresett;
    while (mozgo != NULL) {
        db++;
        mozgo = mozgo->kov;
    }
    int talalat = 0;
    KlistaElem *ker = keresett;
    for (int i = 0; i < db; ++i) {
        mozgo = aktualis->hozz_menny;
        while (mozgo != NULL) {
            if (strcmp(mozgo->hozzavalo, ker->hozzavalo) == 0) {
                talalat++;
            }
            mozgo = mozgo->kov;
        }
        ker = ker->kov;
    }
    if (talalat == 0) {
        return false;
    }
    else if (db == talalat) {
        printf("\t%d. %s\n", aktualis->sorszam, aktualis->nev);
        return true;
    }
    return false;
}
void reszletek(NagyLista *rec_konyv) {
    printf("\n---------------------------------------------------"
           "\nRecept r�szletei (sorsz�m vagy '0'-vissza):\n");
    int reszlet;
    scanf("%d", &reszlet);
    getchar();

    if (reszlet == 0)
        return;
    else {
        ListaElem *mozgo = rec_konyv->elso->kov;
        while (mozgo->sorszam != reszlet) {
            mozgo = mozgo->kov;
        }
        system("cls");
        printf("\n\t\t\t%s"
               "\n--------------------------------------------------------------------------------", mozgo->nev);
        printf("\nHozz�val�k:"
               "\n-----------\n\n");

        KlistaElem *kmozgo = mozgo->hozz_menny;
        while (kmozgo != NULL) {
            printf("\t%s - %s\n", kmozgo->hozzavalo, kmozgo->mennyiseg);
            kmozgo = kmozgo->kov;
        }
        printf("\n--------------------------------------------------------------------------------"
               "\nElk�sz�t�s:"
               "\n-----------\n\n");
        printf("%s\n", mozgo->elkeszites);
        printf("\n--------------------------------------------------------------------------------"
               "\nVissza: Enter");
        getchar();
    }
}
KlistaElem *el_kellHozzavalok() {
    KlistaElem *beolv_hozz = NULL;
    char *ujSzo = NULL;
    int i = 0;
    while (strcmp((ujSzo = hosszu_sort_olvas()), "0") != 0) {
        KlistaElem *beolvSeged = (KlistaElem *) malloc(sizeof(KlistaElem));
        beolvSeged->mennyiseg = NULL;
        beolvSeged->kov = NULL;

        beolvSeged->hozzavalo = ujSzo;
        beolvSeged->sorszam = ++i;
        beolv_hozz = uj_elem_hozzafuz(beolv_hozz, beolvSeged);
    }
    free(ujSzo);

    return beolv_hozz;
}
void torles(NagyLista *rec_konyv) {
    printf("\nAdd meg a t�rlend� recept sorsz�m�t ('0'-m�gse):\n");
    int torlendo;
    scanf("%d", &torlendo);
    getchar();
    if (torlendo == 0) return;

    ListaElem *mozgo = rec_konyv->elso->kov;
    while (mozgo->sorszam != torlendo) {
        mozgo = mozgo->kov;
    }
    mozgo->elozo->kov = mozgo->kov;
    mozgo->kov->elozo = mozgo->elozo;

    free(mozgo->nev);
    free(mozgo->elkeszites);
    felszabadit_kisLista(mozgo->hozz_menny);
    free(mozgo);
    mentes(rec_konyv);
    printf("A t�rl�s megt�rt�nt...\n"
           "\nVissza: Enter");
    getchar();
}
void eddigiek_kiir(int almenu, KlistaElem *kisList_uj, ListaElem *uj_beolvasott) {
    if (almenu != '9') { /*ha m�r hozz� lett adva valamilyen hozz�val�, azt ki�rja, hogy tudjuk mi sz�ks�ges m�g*/
        printf("Eddigi hozz�val�k es mennyis�gek ehhez: %s\n", uj_beolvasott->nev);
        KlistaElem *m = kisList_uj;
        while (m != NULL) {
            printf("%s - %s\n", m->hozzavalo, m->mennyiseg);
            m = m->kov;
        }
    } else {
        printf("Add meg a hozz�val�kat �s mennyis�geket ehhez: %s\n", uj_beolvasott->nev);
    }
}
KlistaElem *almenuFGV(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje, int almenu) {
    if (almenu == '1') { /*�j hozz�val�*/
        system("cls");
        kisList_uj = uj(kisList_uj,beolv_hozzEleje);

    } else if (almenu == '2') { /*f�jlb�l kiv�laszt�s*/
        system("cls");
        kisList_uj = fajl(kisList_uj, beolv_hozzEleje);
    }
    return kisList_uj;
}
KlistaElem *uj(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje) {
    printf("Ha nincs t�bb hozz�val� '0'-�t �rj hozz�val�nak!\n");
    KlistaElem *seged = NULL;
    char *szo = "";
    while (strcmp(szo, "0") != 0) {
        seged = egy_elem(); //bekeri a hozzavalot es a mennyiseget
        szo = seged->hozzavalo;

        if (strcmp(seged->hozzavalo, "0") != 0) {
            kisList_uj = uj_elem_hozzafuz(kisList_uj, seged);
            beolv_hozzEleje = megvizsgal(beolv_hozzEleje, seged);
        }
    }
    free(seged->hozzavalo);
    free(seged->mennyiseg);
    free(seged);
    return kisList_uj;
}
KlistaElem *fajl(KlistaElem *kisList_uj, KlistaElem *beolv_hozzEleje) {
    printf("\tF�jlb�l kiv�laszt�s:\n");
    KlistaElem *mozgo = beolv_hozzEleje;
    while (mozgo != NULL) {
        printf("\t%d.) %s\n", mozgo->sorszam, mozgo->hozzavalo);
        mozgo = mozgo->kov;
    }
    printf("0. M�gse\n");
    KlistaElem *kivalasztott = fajlbol(beolv_hozzEleje);
    if (kivalasztott != NULL)
        kisList_uj = uj_elem_hozzafuz(kisList_uj, kivalasztott);
    return kisList_uj;
}